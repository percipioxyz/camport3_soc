#ifndef Foundation_Fifo_INCLUDED
#define Foundation_Fifo_INCLUDED

#include "Percipio/Mutex.h"

namespace Percipio {

// ============================================================================
/// A basic Fifo implementation without mutex protected.
///
/// Fifo
/// methods:
///     push(v)
///     pop(v)
///     length()
///     reset()
///     isEmpty()
///     isFull()
// ============================================================================
template <typename T>
class Fifo {
private:
	uint32_t m_depth;	        ///< the depth of Fifo, must be 2^x
	uint32_t m_indexHead;	    ///< data is added at offset (in % m_depth)
	uint32_t m_indexTail;	    ///< data is extracted from off. (out % m_depth)
    bool     m_isInternalBuffer;
    T*       m_buffer;

public:
    Fifo() : m_buffer(NULL) {} // have to call init() later

    Fifo(uint32_t depth, void* buffer = NULL)
        : m_depth(depth), m_indexHead(0), m_indexTail(0)
    {
        // assert ((depth & (depth -1)) == 0);
        if (buffer != NULL)
        {
            m_isInternalBuffer = false;
            m_buffer = static_cast<T*>(buffer);
        } else {
            m_isInternalBuffer = true;
            m_buffer = new T[depth];
        }
    }


    virtual ~Fifo()
    {
        if (m_isInternalBuffer)
        {
            delete []m_buffer;
        }
    }


    inline  int  init(uint32_t depth, void* buffer = NULL)
    {
        if ((depth & (depth - 1)) != 0) {
            return -1;
        }

        m_depth = depth;
        m_indexHead = m_indexTail = 0;
        if (buffer != NULL)
        {
            m_isInternalBuffer = false;
            m_buffer = static_cast<T*>(buffer);
        } else {
            m_isInternalBuffer = true;
            m_buffer = new T[depth];
        }

        return (m_buffer != NULL) ? 0 : -1;
    }

    inline  uint32_t    length()  const   {return m_indexTail - m_indexHead;}
    inline  bool        isEmpty() const   {return length() == 0;}
    inline  bool        isFull()  const   {return length() == m_depth;}
    /// need to check empty by user
    inline  T*          head()            {return &m_buffer[outputIndex()];}
    inline  T*          tail()            {return &m_buffer[(m_indexTail - 1) & (m_depth-1)];}
    /// drop the header node
    inline  void        dropOne()   {if(!isEmpty()) m_indexHead++;}

    virtual void        reset()     {m_indexHead = m_indexTail = 0;}

    /// push v into Fifo, make a copy.
    /// @return 0 if succeed, NOT_ENOUGH_DATA if fifo is full.
    virtual int push(const T &v)
    {
        if (isFull()) {
            return -1;
        }

        m_buffer[inputIndex()] = v;
        m_indexTail++;
        return 0;
    }

    /// pop from Fifo to v
    /// @return 0 if succeed, NOT_ENOUGH_DATA if fifo is empty.
    virtual int pop(T &v)
    {
        if (isEmpty()) {
            return -1;
        }
        v = m_buffer[outputIndex()];
        m_indexHead++;
        return 0;
    }

private:
    inline  uint32_t    inputIndex()     {return m_indexTail & (m_depth-1);}
    inline  uint32_t    outputIndex()    {return m_indexHead & (m_depth-1);}

    Fifo<T> (const Fifo<T>&);
    Fifo<T>& operator = (const Fifo<T>&);
};

// ============================================================================
/// Fifo with mutex protected.
///
/// MutexFifo
/// Methods same to Fifo.
// ============================================================================
template <typename T>
class MutexFifo : public Fifo<T> {
private:
    FastMutex   m_inLock;
    FastMutex   m_outLock;

public:
    MutexFifo(int depth, void* buffer = NULL) : Fifo<T>(depth, buffer) {}
    ~MutexFifo()        {}

    void        reset();        ///< overload Fifo::reset()
    int         push(const T &v);     ///< overload Fifo::push()
    int         pop(T &v);   ///< overload Fifo::pop()
};

template <typename T>
void MutexFifo<T>::reset()
{
    m_inLock.lock();
    m_outLock.lock();

    Fifo<T>::reset();

    m_outLock.unlock();
    m_inLock.unlock();
}

template <typename T>
int MutexFifo<T>::push(const T &v)
{
    int ret;

    m_inLock.lock();
    ret = Fifo<T>::push(v);
    m_inLock.unlock();

    return ret;
}

template <typename T>
int MutexFifo<T>::pop(T &v)
{
    int ret;

    m_outLock.lock();
    ret = Fifo<T>::pop(v);
    m_outLock.unlock();

    return ret;
}



}

#endif

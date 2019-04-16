#ifndef Foundation_FileStdio_INCLUDED
#define Foundation_FileStdio_INCLUDED


#include "Percipio/Foundation.h"
#include <string>
#include <stdio.h>


namespace Percipio {


class FileStdio
    /// Wrapper of file operations in stdio.h
{
public:
    FileStdio();
    ~FileStdio();

    bool open(const std::string& path, const std::string& mode);
        /// fp = fopen(path, mode)

    void close();
        /// fclose(fp)

    long size(); 
        /// file total size

    int seek(long offset, int whence);
        /// fseek(fp, offset, whence)

    long tell();
        /// ftell(fp)

    size_t read(void* buffer, size_t size);
        /// fread(buffer, 1, size, fp)

    size_t write(const void* buffer, size_t size);
        /// fwrite(buffer, 1, size, fp)

    int flush();
        /// fflush(fp)

private:
    FileStdio(const FileStdio&);
    FileStdio& operator = (const FileStdio&);

    FILE* fp;
};


//
// inline
//
inline FileStdio::FileStdio()
    : fp(NULL)
{
}


inline FileStdio::~FileStdio()
{
    if(fp){
        fclose(fp);
        fp = NULL;
    }
}


inline bool FileStdio::open(const std::string& path, const std::string& mode)
{
    fp = fopen(path.c_str(), mode.c_str());
    return !!fp;
}


inline void FileStdio::close()
{
    fflush(fp);
    fclose(fp);
    fp = NULL;
}


inline long FileStdio::size()
{
    long pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, pos, SEEK_SET);
    return size;
}


inline int FileStdio::seek(long offset, int whence)
{
    return fseek(fp, offset, whence);
}


inline long FileStdio::tell()
{
    return ftell(fp);
}


inline size_t FileStdio::read(void* buffer, size_t size)
{
    return fread(buffer, 1, size, fp);
}


inline size_t FileStdio::write(const void* buffer, size_t size)
{
    return fwrite(buffer, 1, size, fp);
}


inline int FileStdio::flush()
{
    return fflush(fp);
}


}


#endif

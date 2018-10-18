#ifndef Foundation_FileGenerator_INCLUDED
#define Foundation_FileGenerator_INCLUDED


#include <string>
#include "Percipio/Foundation.h"


namespace Percipio {


class Foundation_API FileGenerator {
public:
    enum {
        CATEGORY_STRATEGY_NONE = 0,
        CATEGORY_STRATEGY_DATE
    };

    enum {
        FILENAME_STRATEGY_INTEGER = 0,
        FILENAME_STRATEGY_DATETIME,
    };

    FileGenerator(int category_strategy, int filename_strategy, int index = 0);

	~FileGenerator();

    void resetFileIndex(int index);
    int setRootPath(const std::string& root_path);

    std::string getNewFilePath();

private:
    std::string genNewDirectory();
    std::string genNewFile();

private:
    int         category_strategy;
    int         file_strategy;
    int         file_index;
    std::string root_path;
};


}

#endif

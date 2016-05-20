#pragma once

#include <string>

class FileStorage
{
public:
    FileStorage(const std::wstring initFileName)
        : fileName(initFileName)
    {}

    std::wstring get_file_name() const {return fileName;}
    void set_file_name(const std::wstring &name) {fileName = name;}

private:
    std::wstring fileName;
};



class FileMask : public FileStorage
{
public:
    FileMask(const std::wstring initFileName)
        : FileStorage(initFileName)
    {}
};


class FileToDecode : public FileStorage
{
public:
    FileToDecode(const std::wstring initFileName)
        : FileStorage(initFileName)
    {}
};


class FileResult   : public FileStorage
{
public:
    FileResult(const std::wstring initFileName)
        : FileStorage(initFileName)
    {}
};


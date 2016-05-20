#pragma once

#include <string>
#include <vector>
#include <functional>

#include "filestorage.hpp"


using BYTE = unsigned char;

class Decoder
{
public:
    Decoder();

    void process( const FileMask      &fileMask,
                    const FileToDecode  &fileToDecode,
                    const FileResult    &fileResult,
                    const unsigned       offset,
                    const std::function<BYTE(BYTE,BYTE)> &calcFunction);


    void decode(const FileMask      &fileMask,
                const FileToDecode  &fileToDecode,
                const FileResult    &fileResult,
                const unsigned       offset)
    { process(fileMask, fileToDecode, fileResult, offset, decrypt); }

    void encode(const FileMask      &fileMask,
                const FileToDecode  &fileToDecode,
                const FileResult    &fileResult,
                const unsigned       offset)
    { process(fileMask, fileToDecode, fileResult, offset, enctypt); }

private:

    std::function<BYTE(BYTE,BYTE)> decrypt = [](BYTE data, BYTE mask){ return data - mask; },
                                   enctypt = [](BYTE data, BYTE mask){ return data + mask; } ;

    std::vector<BYTE> open_file(const std::wstring& filename);

    void save_to_file(const std::wstring fileName, const std::vector<BYTE>& data);

};


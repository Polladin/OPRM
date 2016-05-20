
//#include <iostream>
#include <fstream>
#include <assert.h>
#include <locale>

#include "decoder.hpp"

Decoder::Decoder()
{
}


void Decoder::process( const FileMask      &fileMask,
                const FileToDecode  &fileToDecode,
                const FileResult    &fileResult,
                const unsigned       offset,
                const std::function<BYTE(BYTE,BYTE)> &calcFunction)
{
    auto maskData       = open_file(fileMask.get_file_name());
    auto dataToDecode   = open_file(fileToDecode.get_file_name());

    for (unsigned offs = offset; offs < dataToDecode.size(); ++offs)
    {
        dataToDecode[offs] = calcFunction(dataToDecode[offs], maskData[(offs - offset) % maskData.size()]);
    }

    save_to_file(fileResult.get_file_name(), dataToDecode);
}



inline std::wstring lexical_cast_to_wstr(const std::string& arg) {

   std::wstring result;
   std::locale locale;

   // Use specific (character-driven) facet for current result.
   for (std::size_t i= 0; i < arg.size(); ++i) {
      result += std::use_facet<std::ctype<wchar_t> >(locale).widen(arg[i]);
   }

   return result;
}


inline std::string lexical_cast_to_str(const std::wstring& arg) {

   std::string result;
   std::locale locale;

   // Use specific (character-driven) facet for current result.
   for (std::size_t i= 0; i < arg.size(); ++i) {
      result += std::use_facet<std::ctype<wchar_t> >(locale).narrow(arg[i], '?');
   }

   return result;
}



std::vector<BYTE> Decoder::open_file(const std::wstring& filename)
{
    std::ifstream ifs(lexical_cast_to_str(filename).c_str(), std::ios::binary);
    if (!ifs.is_open()) return {};

    ifs.seekg (0,ifs.end);
    unsigned sizeOfFile = ifs.tellg();
    ifs.seekg (0);

    std::vector<BYTE> res(sizeOfFile);

    char c;
    unsigned int idx = 0;

    while (ifs.get(c))
    {
        res[idx++] = c;
    }

    ifs.close();

    assert(idx == res.size());
    assert(ifs.eof());

    return res;
}


void Decoder::save_to_file(const std::wstring fileName, const std::vector<BYTE>& data)
{
    //setlocale( LC_ALL, ".ACP" );
    std::ofstream ofs(lexical_cast_to_str(fileName).c_str(), std::ios::binary);
    if (ofs)
    {
        ofs.write((const char*)(&data[0]), data.size());
        ofs.close();
    }
}





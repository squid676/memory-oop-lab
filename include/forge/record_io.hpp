#pragma once
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
namespace forge {
struct Record { std::uint32_t id; std::string name; double score; };
inline void write_u32(std::ostream& out, std::uint32_t n) { for (int i=0;i<4;++i) out.put(static_cast<char>((n>>(i*8))&0xff)); }
inline std::uint32_t read_u32(std::istream& in) { std::uint32_t n=0; for(int i=0;i<4;++i){ int c=in.get(); if(c==EOF) throw std::runtime_error("truncated record"); n|=std::uint32_t(static_cast<unsigned char>(c))<<(i*8); } return n; }
inline void save_records(const std::string& path, const Record* records, std::uint32_t count) {
    std::ofstream out(path, std::ios::binary); if(!out) throw std::runtime_error("cannot open output file");
    out.write("FORG",4); write_u32(out,count);
    for(std::uint32_t i=0;i<count;++i){ write_u32(out,records[i].id); write_u32(out,static_cast<std::uint32_t>(records[i].name.size())); out.write(records[i].name.data(),static_cast<std::streamsize>(records[i].name.size())); out.write(reinterpret_cast<const char*>(&records[i].score),sizeof(double)); }
    if(!out) throw std::runtime_error("write failed");
}
inline std::uint32_t load_records(const std::string& path, Record* output, std::uint32_t limit) {
    std::ifstream in(path,std::ios::binary); if(!in) throw std::runtime_error("cannot open input file");
    char magic[4]; in.read(magic,4); if(in.gcount()!=4 || std::string(magic,4)!="FORG") throw std::runtime_error("bad file signature");
    auto count=read_u32(in); if(count>limit) throw std::runtime_error("record count exceeds buffer capacity");
    for(std::uint32_t i=0;i<count;++i){ output[i].id=read_u32(in); auto size=read_u32(in); if(size>1'000'000) throw std::runtime_error("name too large"); output[i].name.resize(size); in.read(output[i].name.data(),size); if(static_cast<std::uint32_t>(in.gcount())!=size) throw std::runtime_error("truncated name"); in.read(reinterpret_cast<char*>(&output[i].score),sizeof(double)); if(!in) throw std::runtime_error("truncated score"); }
    return count;
}
}

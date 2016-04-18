#ifndef WAV_HPP
#define WAV_HPP

#include <cstdint>
#include <stdexcept>
#include <fstream>
#include <vector>

#pragma pack(push,1)

namespace wav {
  struct header {
    uint32_t chunkId;
    uint32_t chunkSize;
    uint32_t format;
    uint32_t subchunk1Id;
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    uint32_t subchunk2Id;
    uint32_t subchunk2Size;
  };

  
  struct wav_file{
    header h;
    size_t data_size;
    uint8_t *data;
    void load_file(const char*);
    wav_file(const char*);
    ~wav_file() { delete[] data; }
    std::vector<uint8_t> extract_channel(size_t);
    std::vector<float> ch_to_float_vector(size_t);
  };

  std::vector<float> loadFloatFirstChannel(const char*);

}
#pragma pack(pop)

#include "wav.cpp"

#endif

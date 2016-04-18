#include "wav.hpp"

wav::wav_file::wav_file(const char* path)
{
  load_file(path);
}

void wav::wav_file::load_file(const char *src)
{
  std::ifstream source;
  source.open(src,std::ios::binary);
  if (!source) throw std::invalid_argument("Can't open file!");
  source.read((char*)(&h), sizeof(header));
  data_size = h.subchunk2Size;

  if (data) delete[] data;

  data = new uint8_t [data_size];
  source.read((char*)data,data_size);
  source.close();
}

std::vector<uint8_t> wav::wav_file::extract_channel(size_t num)
{
  auto all_num = h.numChannels;
  if (num > all_num) throw std::invalid_argument("Channel index too large!");

  size_t ret_size = (data_size / all_num);
  size_t bpc = (h.blockAlign / all_num);
  std::vector<uint8_t> vret(ret_size);
  
  for (size_t i = 0 + num*bpc, j = 0 ; i < data_size; i += h.blockAlign )
    for (size_t k = 0; k < bpc; k++, j++)
      vret[j] = data[i+k];
  
  return vret;
}

std::vector<float> wav::wav_file::ch_to_float_vector(size_t n)
{
  auto channel = extract_channel(n);
  size_t ssize = h.blockAlign / h.numChannels;
  size_t scount = data_size / h.blockAlign;
  std::vector<float> ret(scount);
  uint32_t temp;
  for (size_t i = 0,k = 0; i < ssize*scount; i+=ssize, k++)
    {
      temp = 0;
      for (size_t j = 0; j < ssize; j++)
        {
          temp = temp << 8; 
          temp += channel[i+j];
        }
      ret[k] =  ((float)temp / (float)UINT32_MAX);
    }
  return ret;
}

std::vector<float> wav::loadFloatFirstChannel(const char *path)
{
  return wav_file(path).ch_to_float_vector(0);
}

#ifndef tPipeH
#define tPipeH

class TPipe
{
public:
  TPipe() = delete;
  TPipe(const TPipe&) = delete;
  TPipe& operator=(const TPipe&) = delete;

  TPipe(const std::string& strPipeName, mode_t mode);

  ~TPipe();

  std::string read();
  void write(const std::string& data);
  
private:
  int m_fifo;
};

#endif
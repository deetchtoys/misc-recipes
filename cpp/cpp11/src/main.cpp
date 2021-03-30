#include <iostream>

#include "./test/TestRunner.h"

using namespace std;

class CompanyA {
 public:
  void sendCleartext(const std::string& msg)
  {
    cout << "CompanyA: sendCleartext" << endl;
  }

  void sendEncrypted(const std::string& msg)
  {
    cout << "CompanyA: sendEncrypted" << endl;
  }
};

class CompanyB {
  public:
  void sendCleartext(const std::string& msg)
  {
    cout << "CompanyB: sendCleartext" << endl;
  }

  void sendEncrypted(const std::string& msg)
  {
    cout << "CompanyB: sendEncrypted" << endl;
  }
};

class CompanyZ {
public:
  void sendEncrypted(const std::string& msg)
  {
    cout << "CompanyZ: sendEncrypted" << endl;
  }
};

class MsgInfo {

};

template<class Company>
class MsgSender {
 public:
  void sendClear(const MsgInfo &info)
  {
    std::string msg;
    Company c;
    c.sendCleartext(msg);
  }

  void sendSecret(const MsgInfo &info)
  {

  }
};

template<class Company>
class LoggingMsgSender : public MsgSender<Company> {
 public:
  void sendClearMsg(const MsgInfo &info)
  {
    this->sendClear(info);
  }
};

int main(int argc, char **argv)
{
    // TestRunner().run(argc, argv);
  MsgSender<CompanyA> msg_sender;
  msg_sender.sendClear({});
  return 0;
}

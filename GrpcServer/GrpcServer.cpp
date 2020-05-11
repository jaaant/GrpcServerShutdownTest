#include "pch.h"

#include "service/service.grpc.pb.h"
#include "grpcpp\grpcpp.h"
#include <iostream>

using namespace grpc;
using namespace std;

class ServiceImpl : public test::MyService::Service {
  Status DoStuff(ServerContext* c, const test::Request* req, test::Response* res) override {
    return Status::OK;
  }
};

unique_ptr<Server> BuildServer(string addr) {
  ServerBuilder builder;
  builder.RegisterService(new ServiceImpl());
  builder.AddListeningPort(addr, InsecureServerCredentials());
  return builder.BuildAndStart();
}

int main() {
  auto server1 = BuildServer("0.0.0.0:5000");
  auto server2 = BuildServer("0.0.0.0:5001");
  cout << "Servers running." << endl;

  Sleep(10*1000);

  cout << "Shutting down." << endl;
  server1->Shutdown();
  server2->Shutdown();

  return 0;
}
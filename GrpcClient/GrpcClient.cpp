#include "pch.h"

#include "service/service.grpc.pb.h"
#include "grpcpp\grpcpp.h"
#include <iostream>

using namespace grpc;
using namespace std;

int main() {
  auto channel = CreateChannel("localhost:5000", InsecureChannelCredentials());
  auto client = test::MyService::NewStub(channel);

  Status status = Status::OK;
  while(status.error_code() == StatusCode::OK) {
    test::Response response;
    status = client->DoStuff(new ClientContext(), {}, &response);
    Sleep(1000);
  }

  cout << status.error_code() << ": " << status.error_message() << endl;

  return 0;
}
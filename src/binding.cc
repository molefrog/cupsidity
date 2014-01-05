// Standard C++ library headers
#include <string>
#include <map>
#include <iostream>
#include <sstream>

// Node.js related headers
#include <node.h>
#include <v8.h>
#include <uv.h>

using namespace v8;


Handle<Value> testFunc(const Arguments& args) {
    HandleScope scope;
	return scope.Close(String::New("Hello, world!"));
}

void RegisterModule(Handle<Object> target) {
 	NODE_SET_METHOD(target, "test", testFunc);

	return;
}

NODE_MODULE(binding, RegisterModule)
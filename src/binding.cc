// Node.js related headers
#include <node.h>
#include <v8.h>
#include <uv.h>

using namespace v8;

// -------------------------------------------------------------------
// Destination related functions (see: dests.cc)
// -------------------------------------------------------------------
Handle<Value> getDests(const Arguments& args);
Handle<Value> getDefault(const Arguments& args);

// -------------------------------------------------------------------
// Job related functions (see: jobs.cc)
// -------------------------------------------------------------------
Handle<Value> getJobs(const Arguments& args);
Handle<Value> cancelJob(const Arguments& args);


void RegisterModule(Handle<Object> target) {
 	NODE_SET_METHOD(target, "getDests", 	getDests);
 	NODE_SET_METHOD(target, "getDefault", 	getDefault);

 	NODE_SET_METHOD(target, "getJobs", 		getJobs);
 	NODE_SET_METHOD(target, "cancelJob", 	cancelJob);

	return;
}

NODE_MODULE(binding, RegisterModule)


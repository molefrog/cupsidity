// Standard C++ library headers
#include <string>

// Node.js related headers
#include <node.h>
#include <v8.h>
#include <uv.h>

// CUPS headers
#include <cups/cups.h>

using namespace v8;

// -------------------------------------------------------------------
// cupsGetJobs() binding 
// Get the jobs from the default server.
// -------------------------------------------------------------------
Handle<Value> getJobs(const Arguments& args) {
	HandleScope scope;

	std::string destName;
	std::string which;

   	const char * destNameC = NULL;
   	bool mine = true;
   	int whichJobs = CUPS_WHICHJOBS_ALL;

	if(args.Length() > 0) {
		Local<Object> configObject = args[0]->ToObject();

	    if(configObject->Has(String::NewSymbol("dest")))
	    	destName = *String::Utf8Value(
	    		configObject->Get(String::NewSymbol("dest") ));

	    if(configObject->Has(String::NewSymbol("mine")))
	    	mine = configObject->Get(String::NewSymbol("mine"))
	    		->ToBoolean()->Value();

	     if(configObject->Has(String::NewSymbol("which"))) {
	    	which = *String::Utf8Value(
	    		configObject->Get(String::NewSymbol("which") ));

	    	if(false);
	    	else if(which == "all") 		whichJobs = CUPS_WHICHJOBS_ALL;
	    	else if(which == "active") 		whichJobs = CUPS_WHICHJOBS_ACTIVE;
	    	else if(which == "completed")	whichJobs = CUPS_WHICHJOBS_COMPLETED;
	     }
	}

   	if(!destName.empty()) {
   		destNameC = destName.c_str();
   	} 


	cups_job_t *jobs;
	// TODO: 2nd and 4th arguments!
	int numJobs = cupsGetJobs(
		&jobs,
		destNameC,	// NULL = all destinations, otherwise show jobs for 
					// named destination
		(int) mine, 		// 0 = all users, 1 = mine
		whichJobs
	);

	Local<Array> jobsArray = Array::New(numJobs);

	cups_job_t * job = jobs;
	for (int jobIdx = 0; jobIdx < numJobs; ++jobIdx, ++job) {

		Local<Object> jobObject = Object::New();

		jobObject->Set(String::NewSymbol("dest"),
			String::New(job->dest));

		jobObject->Set(String::NewSymbol("format"),
			String::New(job->format));

		jobObject->Set(String::NewSymbol("title"),
			String::New(job->title));

		jobObject->Set(String::NewSymbol("user"),
			String::New(job->user));

		jobObject->Set(String::NewSymbol("id"),
			Number::New(job->id));

		jobObject->Set(String::NewSymbol("priority"),
			Number::New(job->priority));

		jobObject->Set(String::NewSymbol("size"),
			Number::New(job->size));

		jobObject->Set(String::NewSymbol("processing_time"),
			Number::New(job->processing_time));

		jobObject->Set(String::NewSymbol("creation_time"),
			Number::New(job->creation_time));

		jobObject->Set(String::NewSymbol("completed_time"),
			Number::New(job->completed_time));

		jobObject->Set(String::NewSymbol("state_number"),
			Number::New(job->state));

		std::string state;
		switch(job->state) {
			case IPP_JOB_PENDING: 		
				state = "pending"; 
				break;
			case IPP_JOB_HELD: 		
				state = "held"; 
				break;
			case IPP_JOB_PROCESSING: 	
				state = "processing"; 
				break;
			case IPP_JOB_STOPPED: 		
				state = "stopped"; 
				break;
			case IPP_JOB_CANCELLED: 	
				state = "cancelled"; 
				break;
			case IPP_JOB_ABORTED: 		
				state = "aborted"; 
				break;
			case IPP_JOB_COMPLETED: 	
				state = "completed"; 
				break;
			default: state = "unknown";
		}

		jobObject->Set(String::NewSymbol("state"),
			String::New(state.c_str()));

		jobsArray->Set(jobIdx, jobObject);
	}


	cupsFreeJobs(numJobs, jobs);
	return scope.Close( jobsArray );
}

// -------------------------------------------------------------------
// cupsCancelJob() binding 
// Cancel a print job on the default server.
// -------------------------------------------------------------------
Handle<Value> cancelJob(const Arguments& args) {
	HandleScope scope;

	Local<Object> configObject = args[0]->ToObject();

    int jobId = 0;
    if(configObject->Has(String::NewSymbol("id")))
    	jobId = configObject->Get(String::NewSymbol("id") )
    		->ToNumber()->Value();

	std::string destName;
    if(configObject->Has(String::NewSymbol("dest")))
    	destName = *String::Utf8Value(
    		configObject->Get(String::NewSymbol("dest") ));

	int success = cupsCancelJob( destName.c_str(), jobId );

	return scope.Close( Boolean::New( success) );
}


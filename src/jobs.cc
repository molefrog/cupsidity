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

	cups_job_t *jobs;

	// TODO: 2nd and 4th arguments!
	int numJobs = cupsGetJobs(
		&jobs,
		NULL,	// NULL = all destinations, otherwise show jobs for 
				// named destination
		1, 		// 0 = all users, 1 = mine
		CUPS_WHICHJOBS_ACTIVE
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

		// TODO: Date object
		jobObject->Set(String::NewSymbol("processing_time_unix"),
			Number::New(job->processing_time));

		jobObject->Set(String::NewSymbol("creation_time_unix"),
			Number::New(job->creation_time));

		jobObject->Set(String::NewSymbol("completed_time_unix"),
			Number::New(job->completed_time));

		// TODO:
		// job->state:
		//	IPP_JOB_PENDING = 3,
		//	IPP_JOB_HELD = 4,
		//	IPP_JOB_PROCESSING = 5,
		//	IPP_JOB_STOPPED = 6,
		//	IPP_JOB_CANCELLED = 7,
		//	IPP_JOB_ABORTED = 8,
		//	IPP_JOB_COMPLETED = 9
		jobObject->Set(String::NewSymbol("state"),
			Number::New(job->state));

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

	// TODO: parse arguments!
	// Job ID, CUPS_JOBID_CURRENT for the current job, or CUPS_JOBID_ALL for all jobs
	int jobId = 0;

	const char * destName = "";

	int success = cupsCancelJob( destName, jobId );

	return scope.Close( Boolean::New( success) );
}


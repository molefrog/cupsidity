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
// cupsGetDests() binding 
// Get the list of destinations from the default server.
// -------------------------------------------------------------------
Handle<Value> getDests(const Arguments& args) {
	HandleScope scope;

	cups_dest_t *dests;
	int num_dests = cupsGetDests(&dests);

	if(num_dests < 0) {
		return scope.Close(Undefined());
	}


	Local<Array> destArray = Array::New(num_dests);

	cups_dest_t * dest = dests;
	for (int destIdx = 0; destIdx < num_dests; ++destIdx, ++dest) {

		Local<Object> destObject = Object::New();

		destObject->Set(String::NewSymbol("name"),
			String::New(dest->name));

		// Instance can be NULL
		if(dest->instance != NULL) {		
			destObject->Set(String::NewSymbol("instance"),
				String::New(dest->instance));
		}


		destObject->Set(String::NewSymbol("is_default"),
			Boolean::New(dest->is_default));

		// Fill printer's options
		Local<Object> optionsObject = Object::New();
		for(int optIdx = 0; optIdx < dest->num_options; ++optIdx) {
			
			optionsObject->Set(
				String::New( dest->options[optIdx].name ),
				String::New( dest->options[optIdx].value )
			);
		}

		destObject->Set(String::NewSymbol("options"),
			optionsObject);

		destArray->Set(destIdx, destObject);
	}


	cupsFreeDests(num_dests, dests);
	return scope.Close( destArray );
}

// -------------------------------------------------------------------
// cupsGetDefault() binding 
// Get the default printer or class for the default server.
// -------------------------------------------------------------------
Handle<Value> getDefault(const Arguments& args) {
	HandleScope scope;

	Local<String> defaultDest = 
		String::New( cupsGetDefault() );

	return scope.Close(defaultDest);
}

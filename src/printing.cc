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
// cupsPrintFile() binding 
// Print a file to a printer or class on the default server.
// -------------------------------------------------------------------
Handle<Value> printFile(const Arguments& args) {
	HandleScope scope;

    Local<Object> configObject = args[0]->ToObject();

    std::string dest, title, filename;

    if(configObject->Has(String::NewSymbol("dest")))
    	dest = *String::Utf8Value(
    		configObject->Get(String::NewSymbol("dest") ));

    if(configObject->Has(String::NewSymbol("title")))
    	title = *String::Utf8Value(
    		configObject->Get(String::NewSymbol("title") ));

	if(configObject->Has(String::NewSymbol("filename")))
		filename = *String::Utf8Value(
    		configObject->Get(String::NewSymbol("filename") ));

	cups_option_t *options = NULL;
	int numOptions = 0;

	// Get options object and transform into the cups options format
    if(configObject->Has(String::NewSymbol("options"))) {
        Local<Object> optionsObject = configObject
            ->Get(String::NewSymbol("options"))->ToObject();

        Local<Array> properties = optionsObject->GetPropertyNames();

        // Iterate over 'options' object keys
        for(unsigned int i = 0; i < properties->Length(); ++i) {
            Local<String> keyString = properties->Get(i)->ToString();
            Local<String> valueString = optionsObject->Get(keyString)->ToString();

            std::string keyStringStd = std::string(
            	*String::Utf8Value(keyString));

            std::string valueStringStd = std::string(
            	*String::Utf8Value(valueString));

			numOptions = cupsAddOption(keyStringStd.c_str(), valueStringStd.c_str(), 
				numOptions, &options);
        }        
    }


	int jobId = cupsPrintFile (dest.c_str(), filename.c_str(), title.c_str(),
	    numOptions, options);

	cupsFreeOptions(numOptions, options);

	return scope.Close( Number::New( jobId ) );
}

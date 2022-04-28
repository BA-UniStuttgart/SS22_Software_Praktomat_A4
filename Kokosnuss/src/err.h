#ifndef _ERR_H_
#define _ERR_H_

// Signalises various error states in the public API
typedef enum KokosErrorType {
	// Signalises a noerr case
	None,

	/*
		Will be set if heap mem
		could not be allocated
	*/
	OutOfMemoryError,

	/*
		Will be set if an input parameter
		is null. Additionally, in KokosError,
		the 'errv' value will be set as the
		input parameters index, with a value of 1 being the
		first argument.
	*/
	NullPointerError

} KokosErrorType;

typedef struct KokosError {
	// The error type
	KokosErrorType error_type;

	/*
		Additional info e.g. in case of NullPointerError.
		If additional info is given it is set to -1. 
		If the ErrorType is None, it is set to 0.
		The errv value of 0 is a reserved value and can be
		reliably matched upon.
	*/
	int errv;

} KokosError;

// Helper function for easier error evaluation
int kokos_has_error(const KokosError* error);

/*
	Helper function to avoid code duplication.
	Returns an KokosError:None
*/
KokosError kokos_noerr();

/*
	Helper function to avoid code duplication.
	Returns an KokosError:OutOfMemoryError
*/
KokosError kokos_memory();

/*
	Helper function to avoid code duplication.
	Returns a KokosError:NullPointerError
	with 'index' being the index of the null argument.
*/
KokosError kokos_nullptr(int index);

#endif
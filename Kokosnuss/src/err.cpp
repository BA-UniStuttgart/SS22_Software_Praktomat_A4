#include "err.h"

// Helper function for easier error evaluation
int kokos_has_error(const KokosError* error) {
	if (!error->errv) {
		return 0;
	}

	return 1;
}

/*
	Helper function to avoid code duplication.
	Returns an KokosError:None
*/
KokosError kokos_noerr() {
	return KokosError{
		None,
		0
	};
}

/*
	Helper function to avoid code duplication.
	Returns an KokosError:OutOfMemoryError
*/
KokosError kokos_memory() {
	return KokosError{
		OutOfMemoryError,
		-1
	};
}

/*
	Helper function to avoid code duplication.
	Returns a KokosError:NullPointerError
	with 'index' being the index of the null argument.
*/
KokosError kokos_nullptr(int index) {
	return KokosError{
		NullPointerError,
		index
	};
}
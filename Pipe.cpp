#include "Pipe.h"
int Pipe::max_id_pipe = 0;
Pipe::Pipe() {
	id_pipe = max_id_pipe++;
}
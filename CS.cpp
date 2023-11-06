#include "CS.h"
int CS::max_id_cs = 0;
CS::CS() {
	id_cs = max_id_cs++;
}
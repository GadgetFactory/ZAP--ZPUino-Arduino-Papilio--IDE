extern unsigned int ___ctors, ___ctors_end;

extern void _Z4loopv();
extern void _Z5setupv();

void ___do_global_ctors()
{
	unsigned int *ptr = &___ctors;
	while (ptr!=&___ctors_end) {
		((void(*)(void))(*ptr))();
		ptr++;
	}
}

int main(int argc, char **argv)
{
	_Z5setupv();
	while (1) {
		_Z4loopv();
	}
}
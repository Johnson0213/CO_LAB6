all:
	g++ direct_mapped_cache.cpp -o direct_mapped_cache.out
	g++ set_associative_cache.cpp -o set_associative_cache.out
	./direct_mapped_cache.out
	./set_associative_cache.out

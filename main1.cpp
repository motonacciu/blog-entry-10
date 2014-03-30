#include <iostream>
#include <array>

typedef enum 
{
#define OPERATOR(NAME,...) NAME,
#include "opcodes.def"
} operator_t;

typedef enum 
{
	reg = 0x00001, 
	imm = 0x00010, 
	lab = 0x00100,
	//...
} type_t;


constexpr inline unsigned option()
{
	return 0u;
}

template <class H, class... ARGS>
constexpr inline unsigned option(const H& head, const ARGS&... args)
{
	return head | option(args...);
}


inline bool is_valid_operator(operator_t opcode, unsigned argidx, type_t type)
{
	switch(opcode)
	{
#define OPTION(...)    (option(__VA_ARGS__))  // for semplicity we limit options to 2
#define OPERATOR(NAME, ARITY, ...) \
	case NAME: \
	{	\
		if (argidx >= ARITY) { return false; } \
		constexpr std::array<unsigned, ARITY> types{ __VA_ARGS__ }; \
		return types[argidx] & type ? true : false;  \
	}
	#include "opcodes.def"
	}	
}

int main(int argc, char* argv[])
{
	std::cout << "Is 'sub(_,_,_,reg)' valid? "
			  << std::boolalpha << is_valid_operator(sub, 3, reg) << std::endl;
	std::cout << "Is 'add(_,reg,_)'   valid? " 
			  << std::boolalpha << is_valid_operator(add, 1, reg) << std::endl;
	std::cout << "Is 'add(_,imm,_)'   valid? "
			  << std::boolalpha << is_valid_operator(add, 1, imm) << std::endl;
	std::cout << "Is 'sub(_,_,imm)'   valid? " 
			  << std::boolalpha << is_valid_operator(sub, 2, imm) << std::endl;
	std::cout << "Is 'sub(_,_,lab)'   valid? "
			  << std::boolalpha << is_valid_operator(sub, 2, lab) << std::endl;
}

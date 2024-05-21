CXX = g++
CXX_FLAGS = -std=c++03 -o $(NAME)
NAME = myfractionclass

all: run clean

compile:
	@$(CXX) Main.cxx TestFraction.cxx Fraction.cxx $(CXX_FLAGS)

run: compile
	@./$(NAME)

clean:
	@rm $(NAME)

write:
	@./$(NAME) > Fraction.output

output: compile write clean
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <deque>
#include <utility>

class PmergeMe {

	private:

		std::list<int> liste;
		std::deque<int> deq;
		std::list<int> smallElements;
		std::deque<int> smallDeque;
	public:

		PmergeMe( std::string av );
		~PmergeMe();

		//list
		bool buildList( std::string av );
		void printList(const std::list<int>& liste);
		bool isDigit(const std::string& numStr);
		void fordJohnsonSortList( std::list<int>& liste);
		void mergeList( std::list<int>& liste, std::list<int>& left, std::list<int>& right, int straggler );
		std::list<int> build_large_list(std::list<int> &pairs, std::list<int>& inputList);
		void recursiveSort(std::list<int>& inputList);



		//deque
		bool buildDeque( std::string av );
		void printDeque(const std::deque<int>& deq);
		void fordJohnsonSortDeque( std::deque<int>& deq);
		void mergeDeque( std::deque<int>& deq, std::deque<int>& left, std::deque<int>& right, int straggler );
		std::deque<int> build_large_deque(std::deque<int> &pairs, std::deque<int>& inputList);
		void recursiveSort(std::deque<int>& inputList);

};

#endif

template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}

template <class T1, class T2> struct pair;

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}

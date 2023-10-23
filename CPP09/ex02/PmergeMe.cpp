#include "PmergeMe.hpp"
#include "Color.hpp"
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

PmergeMe::PmergeMe( std::string av ) {

	timeval start, end;

	//list
	gettimeofday(&start, NULL);
	// unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);
	if( buildList(av) == false ) {
		return;
	}
	gettimeofday(&end, NULL);

	double elapsedTime;

	elapsedTime = (end.tv_sec - start.tv_sec) * 1e6;
    elapsedTime = (elapsedTime + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << GR << "Time to process a range of " << liste.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(6) << elapsedTime << " us" << std::endl;
	std::cout << RES << std::endl;

	// //deque
	timeval startD, endD;
	gettimeofday(&startD, NULL);
    std::ios_base::sync_with_stdio(false);
	buildDeque(av);
	gettimeofday(&endD, NULL);

	double elapsedTimeD;

	elapsedTimeD = (endD.tv_sec - startD.tv_sec) * 1e6;
    elapsedTimeD = (elapsedTimeD + (endD.tv_usec - startD.tv_usec)) * 1e-6;
	std::cout << GR << "Time to process a range of " << deq.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(6) << elapsedTimeD << " us" << std::endl;
	std::cout << RES << std::endl;

}

PmergeMe::~PmergeMe() {}

//list

bool PmergeMe::isDigit(const std::string& numStr) {

    std::string::const_iterator it = numStr.begin();
    while (it != numStr.end()) // && std::isdigit(*it) && *it != '0'
		++it;
    return !numStr.empty() && it == numStr.end();
}

bool PmergeMe::buildList(std::string av) {

	std::istringstream iss(av);
	std::string num_str;
	int num;

	while (iss >> num_str) {

		if (!isDigit(num_str)) {
			std:: cout << "Usage: a positive integer sequence as argument" << std::endl;
			return false;
		}
		num = std::stoi(num_str);
		liste.push_back( num );
	}

	if( liste.size() < 1 ) {

		std::cout << "List is empty" << std::endl;
		return false;
	}

	if( liste.size() == 1 ) {

		if( num == 0 ) {
			std::cout << "Usage: a positive integer sequence as argument" << std::endl;
			return false;
		}
	}

	std::cout << BL << "Ford Johnson Sort List" << std::endl;
	std::cout << BL << "Before:\t";
	printList( liste );
	fordJohnsonSortList( liste);
	return true;
}

void PmergeMe::printList( const std::list<int>& liste ) {

	for( std::list<int>::const_iterator it = liste.begin(); it != liste.end(); it++ ) {

		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void PmergeMe::fordJohnsonSortList( std::list<int>& liste) {

	if( liste.size() <= 1 ) {
		return;
	}

	std::list<int> pairs;

    std::list<int>::iterator it = liste.begin();

     while (it != liste.end()) {
        if (std::next(it) != liste.end()) {
            // Create pairs of elements and add them to 'pairs'
            pairs.push_back(*it);
            pairs.push_back(*std::next(it));
			if (*it > *std::next(it))
				std::swap(*it, *next(it));

            it = std::next(it, 2); // Move to the next pair
        } else {
            // If there's an odd number of elements, leave one unpaired
            pairs.push_back(*it); // Use -1 to indicate unpaired
            break;
        }
    }
	recursiveSort(pairs);
}

void PmergeMe:: recursiveSort(std::list<int>& inputList) {

    if (inputList.size() <= 1) {
        return;
    }

    std::list<int> sortedList;
    // Select larger elements and populate sortedPairs, leaving smaller elements in inputList
    std::list<int> remainingElements = build_large_list(inputList, sortedList);

    // Now, sortedPairs contains larger elements, and inputList contains remaining elements
    // Perform further processing or recursive sorting on sortedPairs if needed

    // Recursive call to sort remainingElements
    recursiveSort(remainingElements);
	sortedList.sort();
	mergeList(inputList, sortedList, this->smallElements, 0);
}


std::list<int> PmergeMe:: build_large_list(std::list<int> &pairs, std::list<int> &sortedList)
{
	std::list<int> remainingElements;

    std::list<int>::iterator it = pairs.begin();

	while (it != pairs.end()) {
        if (std::next(it) != pairs.end()) {
            // Create pairs of elements and add them to 'pairs'
			if (*it > *std::next(it))
			{
				sortedList.push_back(*it);
				this->smallElements.push_back(*std::next(it));
			}
			else {
			{
				sortedList.push_back(*std::next(it));
				this->smallElements.push_back(*it);
			}
			}
			it = std::next(it, 2); // Move to the next pair
		}
		else
		{
			remainingElements.push_back(*it);
			break ;
		}
    }
	return (remainingElements);
}


void PmergeMe::mergeList( std::list<int>& liste, std::list<int>& left, std::list<int>& right, int straggler ) {

	(void)straggler;
	(void)liste;

    std::list<int>::iterator large;
    std::list<int>::iterator small;

	for (small = right.begin(); small != right.end(); small++)
	{
		large = std::upper_bound(left.begin(), left.end(), *small);
		if (large != left.end())
		{
			left.insert(large, *small);
		}
		else
		{
			left.push_back(*small); // Insert at the end if large is at the end
			large = left.begin(); // Update large to point to the beginning of left
		}
	}
		right.clear();

	 std::cout << R << "After: ";

	for (std::list<int>::iterator it = left.begin(); it != left.end(); ++it )
     {
            std::cout << *it << " ";
	 }
	std::cout <<std::endl;
}

// //deque


// bool PmergeMe::isDigit(const std::string& numStr) {

//     std::string::const_iterator it = numStr.begin();
//     while (it != numStr.end()) // && std::isdigit(*it) && *it != '0'
// 		++it;
//     return !numStr.empty() && it == numStr.end();
// }

bool PmergeMe::buildDeque(std::string av) {

	std::istringstream iss(av);
	std::string num_str;
	int num;

	while (iss >> num_str) {

		if (!isDigit(num_str)) {
			std:: cout << "Usage: a positive integer sequence as argument" << std::endl;
			return false;
		}
		num = std::stoi(num_str);
		deq.push_back( num );
	}

	if( deq.size() < 1 ) {

		std::cout << "List is empty" << std::endl;
		return false;
	}

	if( deq.size() == 1 ) {

		if( num == 0 ) {
			std::cout << "Usage: a positive integer sequence as argument" << std::endl;
			return false;
		}
	}

	std::cout << BL << "Ford Johnson Sort Deque" << std::endl;
	std::cout << BL << "Before:\t";
	printDeque( deq );
	fordJohnsonSortDeque( deq);
	return true;
}

void PmergeMe::printDeque( const std::deque<int>& deq ) {

	for( std::deque<int>::const_iterator it = deq.begin(); it != deq.end(); it++ ) {

		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void PmergeMe::fordJohnsonSortDeque( std::deque<int>& deq) {

	if( deq.size() <= 1 ) {
		return;
	}

	std::deque<int> pairs;

    std::deque<int>::iterator it = deq.begin();

     while (it != deq.end()) {
        if (std::next(it) != deq.end()) {
            // Create pairs of elements and add them to 'pairs'
            pairs.push_back(*it);
            pairs.push_back(*std::next(it));
			if (*it > *std::next(it))
				std::swap(*it, *next(it));

            it = std::next(it, 2); // Move to the next pair
        } else {
            // If there's an odd number of elements, leave one unpaired
            pairs.push_back(*it); // Use -1 to indicate unpaired
            break;
        }
    }
	recursiveSort(pairs);
}

void PmergeMe:: recursiveSort(std::deque<int>& inputList) {

    if (inputList.size() <= 1) {
        return;
    }

    std::deque<int> sortedDeque;
    // Select larger elements and populate sortedPairs, leaving smaller elements in inputList
    std::deque<int> remainingElements = build_large_deque(inputList, sortedDeque);

    // Now, sortedPairs contains larger elements, and inputList contains remaining elements
    // Perform further processing or recursive sorting on sortedPairs if needed

    // Recursive call to sort remainingElements
    recursiveSort(remainingElements);
	sort(sortedDeque.begin(), sortedDeque.end());
	mergeDeque(inputList, sortedDeque, this->smallDeque, 0);
}


std::deque<int> PmergeMe:: build_large_deque(std::deque<int> &pairs, std::deque<int> &sortedList)
{
	std::deque<int> remainingElements;

    std::deque<int>::iterator it = pairs.begin();

	while (it != pairs.end()) {
        if (std::next(it) != pairs.end()) {
            // Create pairs of elements and add them to 'pairs'
			if (*it > *std::next(it))
			{
				sortedList.push_back(*it);
				this->smallDeque.push_back(*std::next(it));
			}
			else {
			{
				sortedList.push_back(*std::next(it));
				this->smallDeque.push_back(*it);
			}
			}
			it = std::next(it, 2); // Move to the next pair
		}
		else
		{
			remainingElements.push_back(*it);
			break ;
		}
    }
	return (remainingElements);
}


void PmergeMe::mergeDeque( std::deque<int>& deq, std::deque<int>& left, std::deque<int>& right, int straggler ) {

	(void)straggler;
	(void)deq;

    std::deque<int>::iterator large;
    std::deque<int>::iterator small;

	for (small = right.begin(); small != right.end(); small++)
	{
		large = std::upper_bound(left.begin(), left.end(), *small);
		if (large != left.end())
		{
			left.insert(large, *small);
		}
		else
		{
			left.push_back(*small); // Insert at the end if large is at the end
			large = left.begin(); // Update large to point to the beginning of left
		}
	}
		right.clear();

	 std::cout << R << "After: ";

	for (std::deque<int>::iterator it = left.begin(); it != left.end(); ++it )
     {
            std::cout << *it << " ";
	 }
	std::cout <<std::endl;
}

// void PmergeMe::buildDeque(std::string av) {

// 	std::istringstream iss(av);
// 	std::string num_str;
// 	int num;

// 	while (iss >> num_str) {

// 		if (!isDigit(num_str)) {
// 			log("Usage: a positive integer sequence as argument");
// 			return;
// 		}

// 		num = std::stoi(num_str);
// 		_deque.push_back( num );

// 	}

// 	std::cout << BL << "Ford Johnson Sort Deque" << std::endl;
// 	std::cout << BL << "Before:\t";
// 	printDeque( _deque );

// 	int straggler = 0;

// 	checkDequeStraggler( _deque, straggler );
// 	fordJohnsonSortDeque( _deque, straggler );

// 	std::cout << OR << "After:\t";
// 	printDeque( _deque );
// }

// void PmergeMe::printDeque( const std::deque<int>& _deque ) {

// 	for(  std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); it++ ) {

// 		std::cout << " " << *it;
// 	}
// 	std::cout << std::endl;
// }

// void PmergeMe::checkDequeStraggler( std::deque<int>& _deque, int& straggler ) {

// 	if( _deque.size() <= 1 ) {
// 		return;
// 	}

// 	bool isStraggler = (_deque.size() % 2 == 1);

// 	if( isStraggler ) {

// 		std::deque<int>::iterator its = _deque.end();
// 		--its;
// 		straggler = *its;
// 		_deque.pop_back();
// 	}
// }

// void PmergeMe::fordJohnsonSortDeque( std::deque<int>& _deque, int straggler ) {

// 	if( _deque.size() <= 1 ) {
// 		return;
// 	}

// 	std::deque<int> left;
// 	std::deque<int> right;
// 	int middle = _deque.size() / 2;
// 	int i = 0;

// 	for( std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++ ) {

// 		if( i < middle ) {

// 			left.push_back( *it );
// 		} else {

// 			right.push_back( *it );
// 		}
// 		++i;
// 	}

// 	fordJohnsonSortDeque( left, 0);
// 	fordJohnsonSortDeque( right, 0 );

// 	_deque.clear();
// 	mergeDeque( _deque, left, right, straggler );
// }

// void PmergeMe::mergeDeque( std::deque<int>& _deque, std::deque<int>& leftIt, std::deque<int>& rightIt, int straggler ) {

//     while ( !leftIt.empty() && !rightIt.empty() ) {

//         if ( leftIt.front() <= rightIt.front() ) {
//             _deque.push_back( leftIt.front() );
//             leftIt.pop_front();
//         } else {
//              _deque.push_back( rightIt.front() );
//             rightIt.pop_front();
//         }
//     }

// 	// Add any remaining elements from both containers
//     _deque.insert( _deque.end(), leftIt.begin(), leftIt.end() );
//     _deque.insert( _deque.end(), rightIt.begin(), rightIt.end() );

// 	// Insert the straggler element back into the sorted deque
// 	if( straggler ) {

// 		std::deque<int>::iterator itEnd = _deque.end();
// 		--itEnd;

// 		for( std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++ ) {

// 			if( straggler < *it ) {

// 				_deque.insert( it, straggler );
// 				break;
// 			}

// 			if( straggler > *itEnd ) {

// 				_deque.push_back( straggler );
// 				break;
// 			}
// 		}
// 	}
// }

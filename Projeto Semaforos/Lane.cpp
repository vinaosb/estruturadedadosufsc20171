/*
 * Via.cpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#include "Lane.h"

namespace std {
Lane::Lane() {
	speed_ = -1;
	sizelimit_ = -1;
	lane_ = -1;
}
Lane::Lane(int vel, int lane, int lanesize) {
	speed_ = vel;
	sizelimit_ = lanesize;
	lane_ = lane;
}

Lane::~Lane() {
	clear();
}
void Lane::clear() {
	Node *previous = head;
	while (previous != nullptr) {
		previous = previous->getNext();
		dequeue(0);
	}
	head = nullptr;
	tail = nullptr;
	size_ = 0;
}  // limpar
void Lane::enqueue(int time) {
	Carro* data = carGenerate(time);
	if (empty()) {
		head = new Node(data, nullptr);
		tail = head;
	} else {
		tail->setNext(new Node(data, nullptr));
		tail = tail->getNext();
	}
	carsentered_++;
	current += data->Size();
	data->timeEntry(time);
	size_++;
}
void Lane::enqueue(Carro *data, int time) {
	data->timeEntry(time);
	if (empty()) {
		head = new Node(data, nullptr);
		tail = head;
	} else if (current + data->Size() <= sizelimit_) {
		tail->setNext(new Node(data, nullptr));
		tail = tail->getNext();
	} else {
		throw(out_of_range("A pista esta cheia."));
	}
	carsentered_++;
	current += data->Size();
	size_++;
}
Carro* Lane::dequeue(int time) {
	Carro* back;
	back = nullptr;
	if (empty()) {
		throw(out_of_range("A fila está vazia."));
	}
	if (((head->getData()->timeEntry()/1000) + (sizelimit_ / speed_)) > time/1000) {
		Node *n = head;
		back = n->getData();
		head = head->getNext();
		delete n;
		carsexited_++;
		size_--;
		current -= back->Size();
	}
	return back;
}
Carro* Lane::front() const {
	if (empty()) {
		throw(out_of_range("A fila está vazia."));
	}
	return head->getData();
}
Carro* Lane::back() const {
	if (empty()) {
		throw(out_of_range("A fila está vazia."));
	}
	return tail->getData();
}
bool Lane::empty() const {
	return !size_;
}
size_t Lane::size() const {
	return size_;
}
int Lane::carsEntered(){
	return carsentered_;
}
int Lane::carsExited(){
	return carsexited_;
}
Carro* Lane::carGenerate(int time) {
	return new Carro(
			turnGeneration(1),
			turnGeneration(2),
			time);
}

LANE Lane::turnGeneration(int i){
	LANE s1,s2;
	int temp = rand()%10, temp2 = rand()%10;
	//atribui s1 para as fontes da esquerda
	if(lane_ == O1L || lane_ == N1S || lane_ == S1N){
		if(temp < oitenta10){s1 = C1L;}
		else if(temp < dez80){
			if (lane_ == O1L) {s1 = N1N;}
			else {s1 = O1O;}
		} else {
			if(lane_ == O1L || lane_ == N1S){s1 = S1S;}
			else {s1 = N1N;}
		}
		//atribui s2 para as fontes da esquerda
		if(temp2 < quarenta30) {s2 = L1L;}
		else if (temp2 < trinta40) {s2 = N2N;}
		else {s2 = S2S; }
	//atribui s2 para as fontes da direita
	} else {
		if(temp < quarenta30) {
			if (lane_ == L1O)
				s2 = N2N;
			else
				s2 = L1L;
		}
		else if(temp < trinta40){
			if (lane_ == S2N) {s2 = N2N;}
			else {s2 = N2S;}
		} else {
			s2 = C1O;
		}
		//atribui s1 para as fontes da direita
		if(temp2 < quarenta30) {s1 = O1O;}
		else if (temp2 < trinta40) {s1 = N1N;}
		else {s1 = S1S; }
	}
	if (i == 1)
		return s1;
	else
		return s2;
}

} /* namespace via */

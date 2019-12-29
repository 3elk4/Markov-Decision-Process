#pragma once
#include <iostream>
#include "Constants.h"
#include <map>
#include <list>

using namespace std;

template<class S>
struct step_details {
	S next_state;
	double reward;
	bool is_done;
};

template<class S, class A>
class AbstractMDP
{
public:
	AbstractMDP() {
		n_states = 0;
	}
	virtual void init_transition_probs_and_rewards(const list<S> &) = 0;
	virtual step_details<S> step(const A &, const S &) = 0;

	virtual list<S> get_all_states() final {
		list<S> temp;
		for (auto const& imap : this->transition_probs) {
			temp.push_back(imap.first);
		}
		return temp;
	}

	virtual list<A> get_possible_actions(const S &p) final {
		list<A> temp;
		auto state = transition_probs[p];
		for (auto const& mapi : state) {
			temp.push_back(mapi.first);
		}
		return temp;
	}

	virtual map<S, double> get_next_states(const S &s, const A &a) final {
		try {
			this->transition_probs.at(s).at(a);
		}
		catch (const out_of_range &oor) {
			//TODO: tutaj coœ informuj¹cego, ¿e nastepny krok to wejœcie na scianê
			return map<S, double>(); // empty
		}
		return this->transition_probs.at(s).at(a);
	}

	virtual double get_transition_prob(const S &s1, const A &a, const S &s2) final {
		try {
			this->transition_probs.at(s1).at(a).at(s2);
		}
		catch (const out_of_range &oor) {
			return INT_MIN;
		}
		return this->transition_probs[s1][a][s2];
	}

	virtual double get_reward(const S &s1, const A &a, const S &s2) {
		try {
			this->rewards.at(s1).at(a).at(s2);
		}
		catch (const out_of_range &oor) {
			return INT_MIN;
		}
		return this->rewards[s1][a][s2];
	}

protected:
	map<S, map<A, map<S, double>>> transition_probs;
	map<S, map<A, map<S, double>>> rewards;
	S current_state;
	S initial_state;
	int n_states;
};


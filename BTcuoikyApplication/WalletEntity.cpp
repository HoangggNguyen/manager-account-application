#include <iostream>
#include <string>
#include <ctime>

class WalletEntity {
private:
	int id;
	std::string numWallet;
	int accountId;
	std::string isActive;
	double amount;

public:
	WalletEntity() {}

	WalletEntity(int& id, std::string& numWallet, int& accountId, std::string& isActive, double& amount)
		: id(id), numWallet(numWallet), accountId(accountId), isActive(isActive), amount(amount) {
	}
	// Getter and Setter for id
	int getId() const {
		return id;
	}
	void setId(int id) {
		this->id = id;
	}

	// Getter and Setter for accountId
	std::string getNumWallet() const {
		return numWallet;
	}
	void setNumWallet(std::string numWall) {
		this->numWallet = numWall;
	}

	// Getter and Setter for accountId
	int getAccountId() const {
		return accountId;
	}
	void setAccountId(int accountId) {
		this->accountId = accountId;
	}
	// Getter and Setter for isActive
	std::string getIsActive() const {
		return isActive;
	}
	void setIsActive(std::string active) {
		isActive = active;
	}
	// Getter and Setter for amount
	double getAmount() const {
		return amount;
	}
	void setAmount(double amount) {
		this->amount = amount;
	}

};
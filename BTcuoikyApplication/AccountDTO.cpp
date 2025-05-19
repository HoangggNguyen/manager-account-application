#include <iostream>
#include <string>
#include <ctime>

class AccountDTO {
private:
	std::string userName;
	std::string isActive;
	std::string createdDate;
	std::string maker;
	std::string isAdmin;
	std::string fullName;
	std::string date_of_birth;
	std::string address;
	std::string phonenumber;
	std::string email;
	std::string gender;

public:
	AccountDTO() {}

	AccountDTO(std::string userName, std::string createdDate, std::string maker, std::string isAdmin,
		std::string fullName, std::string dateOfBirth, std::string address,
		std::string phoneNumber, std::string email, std::string gender)
		: userName(userName), createdDate(createdDate), maker(maker), isAdmin(isAdmin),
		fullName(fullName), date_of_birth(dateOfBirth), address(address),
		phonenumber(phoneNumber), email(email), gender(gender) {
	}
	//getter and setter for fullname
	std::string getFullName() const {
		return fullName;
	}
	void setFullName(const std::string& name) {
		fullName = name;
	}
	std::string getDateOfBirth() const {
		return date_of_birth;
	}
	void setDateOfBirth(const std::string& dob) {
		date_of_birth = dob;
	}
	std::string getAddress() const {
		return address;
	}
	void setAddres(const std::string& add) {
		address = add;
	}
	std::string getPhoneNumber() const {
		return phonenumber;
	}
	void setPhoneNumber(const std::string& phone) {
		phonenumber = phone;
	}
	std::string getEmail() const {
		return email;
	}
	void setEmail(const std::string& mail) {
		email = mail;
	}
	std::string getGender() const {
		return gender;
	}
	void setGender(const std::string& sex) {
		gender = sex;
	}
	std::string getIsAdmin() const {
		return isAdmin;
	}
	void setIsAdmin(const std::string& roleAdmin) {
		isAdmin = roleAdmin;
	}
	std::string getMaker() const {
		return maker;
	}
	void setMaker(const std::string& makerInput) {
		maker = makerInput;
	}
	std::string getCreatedDate() const {
		return createdDate;
	}
	void setCreatedDate(const std::string& dateCreated) {
		createdDate = dateCreated;
	}
	std::string getIsActive() const {
		return isActive;
	}
	void setIsActive(const std::string& active) {
		isActive = active;
	}
	std::string getUserName() const {
		return userName;
	}
	void setUserName(const std::string& nameUser) {
		userName = nameUser;
	}
};
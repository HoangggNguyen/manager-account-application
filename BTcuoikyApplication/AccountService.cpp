#include <iostream>
#include "AccountRepo.cpp"
#include "WalletRepo.cpp"
#include <fstream>
#include <vector>

class AccountService
{
private:
	AccountRepo accountRepository;
	WalletRepo walletRepository;

public:
	std::string encrypt(const std::string& password, const std::string& key) {
		std::string encrypted = password;
		for (size_t i = 0; i < password.size(); i++) {
			encrypted[i] = password[i] ^ key[i % key.size()];
		}
		return encrypted;
	}

	std::string decrypt(const std::string& encrypted, const std::string& key) {
		std::string decrypted = encrypted;
		for (size_t i = 0; i < encrypted.size(); i++) {
			decrypted[i] = encrypted[i] ^ key[i % key.size()];
		}
		return decrypted;
	}

	string generateRandom(std::string& type) {
		const char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		if (type == "number") {
			chars = "0123456789";
		}

		const int length = 8;
		std::string password;
		srand(time(0));
		for (int i = 0; i < length; ++i) {
			password += chars[rand() % (sizeof(chars) - 1)];
		}
		return password;
	}

	bool parseDate(const std::string& dateStr, std::tm& tm) {
		int day, month, year;
		char sep1, sep2;

		std::istringstream ss(dateStr);
		ss >> day >> sep1 >> month >> sep2 >> year;

		if (ss.fail() || sep1 != '/' || sep2 != '/') {
			return false;
		}

		tm = {};
		tm.tm_mday = day;
		tm.tm_mon = month - 1;
		tm.tm_year = year - 1900;

		return true;
	}

	void createAccount(const std::string& userName, const std::string& password, bool isActive, const std::string marker)
	{
		if (password.empty()) {
			std::string type = "text";
			std::string randomPass = generateRandom(type);
			randomPass = encrypt(randomPass, userName);
			accountRepository.createAccount(userName, randomPass, isActive, marker);
		}
		else {
			std::string encrytedPassword = encrypt(password, userName);
			accountRepository.createAccount(userName, encrytedPassword, isActive, marker);
		}
		std::cout << "Tao tai khoan thanh cong" << std::endl;
	}

	void createPersonalUser(std::string& fullName, time_t& dateOfBirth, bool& gender, std::string& address, std::string& phoneNumber, std::string& email, int& accountId)
	{
		accountRepository.createPersonalUser(fullName, dateOfBirth, gender, address, phoneNumber, accountId, email);
		std::cout << "Tao thong tin tai khoan thanh cong" << std::endl;
	}

	void deleteAccount(const std::string& userName)
	{
		accountRepository.deleteAccount(userName);
	}

	void deleteAccountPersonal(const int accountId)
	{
		accountRepository.deleteAccountPersonal(accountId);
	}

	void updateAccountPersonal(std::string& fullName, time_t& dateOfBirth, bool& gender, std::string& address, std::string& phoneNumber, std::string& email, int& accountId)
	{
		accountRepository.deleteAccountPersonal(accountId);
		inputPersonalForm(fullName, dateOfBirth, gender, address, phoneNumber);
		accountRepository.createPersonalUser(fullName, dateOfBirth, gender, address, phoneNumber, accountId, email);
	}

	bool checkAccountLogin(const std::string& userName, const std::string& password)
	{
		std::string passwordEncrypt = encrypt(password, userName);
		return accountRepository.checkAccountLogin(userName, passwordEncrypt);
	}

	AccountEntity getAccountByUserName(const std::string& userName)
	{
		AccountEntity accountEntity = accountRepository.getAccount(userName);
		accountEntity.setPassword(decrypt(accountEntity.getPassword(), userName));
		return accountEntity;
	}

	void printAccount(std::string& userName)
	{
		try {
			AccountEntity accountEntity = getAccountByUserName(userName);
			if (accountEntity.getUserName().empty()) {
				std::cout << "Khong tim thay tai khoan." << std::endl;
				return;
			}
			int accountId = accountEntity.getId();
			PersonalUser personalEntity = accountRepository.getPersonalUserByAccountId(accountId);

			std::cout << "Thong tin tai khoan" << std::endl;
			std::cout << "ten dang nhap: " << accountEntity.getUserName() << std::endl;
			std::cout << "mat khau: " << accountEntity.getPassword() << std::endl;
			std::cout << "hoat dong: " << accountEntity.getIsActive() << std::endl;

			if (!personalEntity.getFullName().empty()) {
				std::cout << "ho va ten: " << personalEntity.getFullName() << std::endl;
			}
			if (!personalEntity.getDateOfBirth().empty()) {
				std::cout << "ngay sinh: " << personalEntity.getDateOfBirth() << std::endl;
			}
			if (!personalEntity.getEmail().empty()) {
				std::cout << "email: " << personalEntity.getDateOfBirth() << std::endl;
			}
			if (!personalEntity.getAddress().empty()) {
				std::cout << "dia chi: " << personalEntity.getDateOfBirth() << std::endl;
			}
			if (!personalEntity.getGender().empty()) {
				std::cout << "gioi tinh: " << personalEntity.getDateOfBirth() << std::endl;
			}
			if (!personalEntity.getPhoneNumber().empty()) {
				std::cout << "so dien thoai: " << personalEntity.getDateOfBirth() << std::endl;
			}
		}
		catch (const std::exception& e) {
			std::cout << "Khong tim thay tai khoan." << std::endl;
			return;
		}
	}

	void printAccountToFile(const AccountEntity& accountEntity)
	{
		std::cout << "Thong tin tai khoan" << std::endl;
		std::cout << "ten dang nhap: " << accountEntity.getUserName() << std::endl;
		std::cout << "mat khau: " << accountEntity.getPassword() << std::endl;
	}

	void updatePassWord(const AccountEntity& accountEntity) {
		std::string passWord;
		std::string newPassWord;
		std::string confirmPass;
		if (accountEntity.getIsActive()) {
			std::cout << "Nhap mat khau: ";
			std::cin >> passWord;

			std::cout << "Nhap mat khau moi: ";
			std::cin >> newPassWord;

			std::cout << "Nhap lai mat khau moi: ";
			std::string confirmPass;

			std::string otpInput;

			std::cout << "Nhap so OTP xac nhan thay doi mat khau" << std::endl;
			std::string type = "text";
			std::string otp = generateRandom(type);
			std::cout << otp << std::endl;
			std::cin >> otpInput;

			if ((newPassWord == "" || confirmPass == "") && newPassWord != confirmPass) {
				std::cout << "Mat khau khong khop." << std::endl;
				return;
			}

			passWord = encrypt(passWord, accountEntity.getUserName());
			if (accountEntity.getPassword() != passWord) {
				std::cout << "Mat khau cu khong dung." << std::endl;
				return;
			}

			if (otp != otpInput) {
				std::cout << "So Otp khong khop." << std::endl;
				return;
			}

			newPassWord = encrypt(newPassWord, accountEntity.getUserName());
			accountRepository.updatePass(accountEntity.getUserName(), newPassWord);
			std::cout << "Cap nhat mat khau thanh cong" << std::endl;
		}
		else {
			std::cout << "Tai khoan hien dang khoa" << std::endl;
		}
	}

	void inputAccountForm(std::string& userName, std::string& password, std::string& confirmPass, std::string& email, bool& isAdmin) {
		int isAdminInput;

		std::cout << "Nhap ten user: ";
		std::cin >> userName;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Nhap mat khau: ";
		std::getline(std::cin, password);

		if (password != "") {
			std::cout << "Nhap lai mat khau: ";
			std::cin >> confirmPass;
		}

		std::cout << "Nhap email: ";
		std::cin >> email;

		std::cout << "Co phai quan tri vien(1 = Co, 0 = Khong): ";
		std::cin >> isAdminInput;
		isAdmin = (isAdminInput != 0);
	}

	void inputPersonalForm(
		std::string& fullName,
		time_t& dateOfBirth,
		bool& gender,
		std::string& address,
		std::string& phoneNumber
	) {
		std::string dateStr;
		int genderInput;

		std::cin.ignore();
		std::cout << "Nhap ho va ten: ";
		std::getline(std::cin, fullName);

		std::cout << "Nhap ngay sinh (dd/mm/yyyy): ";
		std::getline(std::cin, dateStr);

		std::tm tm = {};
		if (parseDate(dateStr, tm)) {
			dateOfBirth = std::mktime(&tm);
		}

		std::cout << "Nhap gioi tinh (1 = Nam, 0 = Nu): ";
		std::cin >> genderInput;
		gender = (genderInput != 0);

		std::cin.ignore();
		std::cout << "Nhap dia chi: ";
		std::getline(std::cin, address);

		std::cout << "Nhap so dien thoai: ";
		std::cin >> phoneNumber;
	}

	void createAcc(std::string& userName,
		std::string& password,
		std::string& confirmPass,
		std::string& fullName,
		time_t& dateOfBirth,
		bool& gender,
		std::string& address,
		std::string& email,
		std::string& phoneNumber,
		AccountEntity& accountEntity,
		bool& isAdmin
	) {
		inputAccountForm(userName, password, confirmPass, email, isAdmin);
		try {
			accountEntity = getAccountByUserName(userName);
			if (!accountEntity.getUserName().empty()) {
				std::cout << "Tai khoan da ton tai." << std::endl;
				return;
			}
			if (password != "" && confirmPass != "" && password != confirmPass) {
				std::cout << "Mat khau khong khop." << std::endl;
				return;
			}
			std::string maker = "admin";;

			if (!accountEntity.getUserName().empty()) {
				maker = accountEntity.getUserName();
			}
			createAccount(userName, password, true, maker);
			accountEntity = getAccountByUserName(userName);
			if (accountEntity.getId() == NULL) {
				std::cout << "Khong tim thay thong tin tai khoan." << std::endl;
				return;
			}
			else {
				inputPersonalForm(fullName, dateOfBirth, gender, address, phoneNumber);
				int accountId = accountEntity.getId();
				createPersonalUser(fullName, dateOfBirth, gender, address, phoneNumber, email, accountId);

				std::string optionSelectExport;
				std::cout << "Xac nhan xuat thong tin tai khoan(Y/N)";
				std::cin >> optionSelectExport;
				if ((optionSelectExport == "Y" || optionSelectExport == "y") && !accountEntity.getUserName().empty()) {
					printAccountToFile(accountEntity);
				}
			}
		}
		catch (const std::exception& e) {
			return;
		}
	}

	void exportAccountsToCSV() {
		try {
			const std::string filePath = "accounts.csv";
			std::ofstream outFile(filePath);
			if (!outFile.is_open()) {
				std::cerr << "Khong mo duoc file: " << filePath << "\n";
				return;
			}
			std::vector<AccountDTO> accounts = accountRepository.findAllActiveAccounts();
			if (!accounts.empty()) {
				outFile << "user_name,created_date,maker,is_admin,fullname,date_of_birth, address, phonenumber, email, gender\n";

				for (const auto& acc : accounts) {
					outFile << acc.getUserName() << ","
						<< acc.getCreatedDate() << ","
						<< acc.getMaker() << ","
						<< acc.getIsAdmin() << ","
						<< acc.getFullName() << ","
						<< acc.getDateOfBirth() << ","
						<< acc.getPhoneNumber() << ","
						<< acc.getEmail() << ","
						<< acc.getGender() << "\n";
				}

				outFile.close();
				std::cout << "Xuat file CSV thanh cong: " << filePath << "\n";
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Loi: " << e.what() << "\n";
			return;
		}
	}

	void createWallet(int& accountId) {
		double amount = 0;
		std::cout << "Nhap so diem muon nap";
		std::cin >> amount;
		std::string type = "number";
		std::string numWall = generateRandom(type);

		walletRepository.createWallet(accountId, amount, numWall);

	}

	void getWalletByAccountId(int& accountId) {
		std::vector<WalletEntity> walletEntities = walletRepository.findAllActiveWallets(accountId);
		if (walletEntities.empty()) {
			std::cout << "Khong tim thay vi diem." << std::endl;
			return;
		}
		for (const auto& wallet : walletEntities) {
			std::cout << "So vi: " << wallet.getNumWallet() << std::endl;
			std::cout << "So diem: " << wallet.getAmount() << std::endl;
			std::cout << "Tinh trang: " << wallet.getIsActive() << std::endl;
		}
	}

	void lockOrUnlockWallet(const WalletEntity& walletEntity) {
		int id = walletEntity.getId();
		bool isActive = walletEntity.getIsActive() == "Hoat dong" ? true : false;

		walletRepository.lockWallet(id, isActive);
		if (isActive) {
			std::cout << "Khoa vi thanh cong" << std::endl;
		}
		else {
			std::cout << "Mo khoa vi thanh cong" << std::endl;
		}
	}

	void updateAmountWallet(std::string& numWallet, double& amount, std::string& type) {
		double amountInput = 0;
		double amountRecive = 0;
		bool isConfirm = false;
		std::string otpInput;

		if (type == "nap") {
			std::cout << "Nhap so diem muon nap them" << std::endl;
			std::cin >> amountInput;
			amountRecive = amount + amountInput;
		}
		else {
			std::cout << "Nhap so diem muon chuyen" << std::endl;
			std::cin >> amountInput;
			if (amountInput < amount) {
				std::cout << "So du diem trong vi khong du" << std::endl;
				return;
			}
			amountRecive = amount - amountInput;
		}
		std::cout << "Nhap so otp" << std::endl;
		std::string type = "number";
		std::string otp = generateRandom(type);
		std::cout << otp << std::endl;
		std::cin >> otpInput;
		if (otp != otpInput) {
			std::cout << "So otp khong khop" << std::endl;
			return;
		}
		else {
			isConfirm = true;
		}

		if (isConfirm) {
			walletRepository.updateAmountWallet(numWallet, amountRecive);
			std::cout << "Thao tac thanh cong" << std::endl;
		}
	}

	WalletEntity getDetailWallet(int& id) {
		return walletRepository.getWalletById(id);
	}

	WalletEntity getDetailWalletByNumWall(std::string& numWall) {
		return walletRepository.getDetailWalletByNumWall(numWall);
	}

	void printInfoWallet(const WalletEntity& walletEntity) {
		if (walletEntity.getId() == 0) {
			std::cout << "Khong tim thay vi." << std::endl;
			return;
		}
		std::cout << "Thong tin vi" << std::endl;
		std::cout << "So vi: " << walletEntity.getNumWallet() << std::endl;
		std::cout << "So diem: " << walletEntity.getAmount() << std::endl;
		std::cout << "Tinh trang: " << walletEntity.getIsActive() << std::endl;
	}

	void transferPoints(const WalletEntity& walletEntity) {
		std::string numWall;
		std::string numWallTransfer = walletEntity.getNumWallet();
		double amount = walletEntity.getAmount();
		std::string type = "chuyen";

		std::cout << "Nhap so vi nhan" << std::endl;
		std::cin >> numWall;
		WalletEntity walletEntityRecive = getDetailWalletByNumWall(numWall);


		if (walletEntityRecive.getId() == 0) {
			std::cout << "Khong tim thay vi" << std::endl;
			return;
		}
		//cap nhat so du vi chuyen
		updateAmountWallet(numWallTransfer, amount, type);
		//cap nhat so du vi nhan
		type = "nhan";
		double amountRecive = walletEntityRecive.getAmount();
		updateAmountWallet(numWall, amountRecive, type);
		std::cout << "Chuyen diem thanh cong" << std::endl;
	}

};
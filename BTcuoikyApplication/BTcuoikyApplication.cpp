#include <stdlib.h>
#include <iostream>
#include "AccountService.cpp"
using namespace std;
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

int printMenu(const std::vector<std::string>& menuItems) {
	for (size_t i = 0; i < menuItems.size(); ++i) {
		std::cout << (i + 1) << ". " << menuItems[i] << "\n";
	}
	std::cout << "================\n";
	std::cout << "Nhap lua chon (1-" << menuItems.size() << "): ";

	int choice = 0;
	std::cin >> choice;

	if (choice < 1 || choice > static_cast<int>(menuItems.size())) {
		return -1;
	}

	return choice;
}

void handleWalletMenu(AccountService& accountService, int accountId,
	const std::vector<std::string>& walletMenu,
	const std::vector<std::string>& walletDetailMenu) {
	bool isInWalletList = true;
	std::string numWallet;
	double amount = 0;
	std::string type;

	while (isInWalletList) {
		int choice = printMenu(walletMenu);
		switch (choice) {
		case 1:
			accountService.createWallet(accountId);
			break;
		case 2: {
			if (accountService.getWalletByAccountId(accountId)) {
				std::cin.ignore();
				std::string numWalletInput;
				int id;
				bool isActive = false;
				double amountInput = 0;

				std::cout << "Nhap so vi muon xem chi tiet: ";
				std::getline(std::cin, numWalletInput);
				if (!numWalletInput.empty()) {
					WalletEntity walletEntity = accountService.getDetailWalletByNumWall(numWalletInput);
					isActive = walletEntity.getIsActive() == "Hoat dong" ? true : false;
					if (walletEntity.getId() != 0) {
						bool isInWallet = true;
						while (isInWallet) {
							int detailChoice = printMenu(walletDetailMenu);
							switch (detailChoice) {
							case 1:
								accountService.printInfoWallet(walletEntity);
								break;
							case 2:
								if (isActive) {
									numWallet = walletEntity.getNumWallet();
									amount = walletEntity.getAmount();
									type = "nap";
									std::cout << "Nhap so diem muon nap them" << std::endl;
									std::cin >> amountInput;
									accountService.updateAmountWallet(numWallet, amount, type, amountInput);
								}
								else {
									std::cout << "Tai khoan da bi khoa" << std::endl;
								}
								break;
							case 3:
								if (isActive) {
									std::cout << "Nhap so vi nhan" << std::endl;
									std::cin >> numWallet;

									std::cout << "Nhap so diem muon chuyen" << std::endl;
									std::cin >> amountInput;
									accountService.transferPoints(walletEntity, amountInput, numWallet);
								}
								else {
									std::cout << "Tai khoan da bi khoa" << std::endl;
								}
								break;
							case 4:
								id = walletEntity.getId();
								accountService.lockOrUnlockWallet(id, isActive);
								break;
							case 5:
								isInWallet = false;
								break;
							case 6:
								exit(0);
							default:
								std::cout << "Lua chon khong phu hop." << std::endl;
							}
						}
					}
				}
			}

			break;
		}
		case 3:
			isInWalletList = false;
			break;
		case 4:
			exit(0);
		default:
			std::cout << "Lua chon khong phu hop." << std::endl;
		}
	}
}


int main() {
	std::string userName, password, confirmPass, fullName, address, email, phoneNumber;
	time_t dateOfBirth = 0;
	bool gender = true, isAdmin = true;
	AccountService accountService;

	std::vector<std::string> mainMenu = {
		"Dang ky tai khoan",
		"Dang nhap",
		"Thoat"
	};

	std::vector<std::string> mainMenuAdmin = {
		"Danh sach tai khoan",
		"Tao tai khoan",
		"Thay doi mat khau",
		"Cap nhat thong tin",
		"Cap nhat thong tin tai khoan user",
		"Quan ly vi diem",
		"Dang xuat",
		"Thoat"
	};

	std::vector<std::string> mainMenuUser = {
		"Thong tin tai khoan",
		"Thay doi mat khau",
		"Cap nhat thong tin",
		"Quan ly vi diem",
		"Dang xuat",
		"Thoat"
	};

	std::vector<std::string> mainMenuWallet = {
		"Tao vi",
		"Xem danh sach vi",
		"Quay lai",
		"Thoat"
	};

	std::vector<std::string> mainMenuWalletDetail = {
		"Xem thong tin vi",
		"Nap diem",
		"Chuyen diem",
		"Khoa/Mo khoa vi",
		"Quay lai",
		"Thoat"
	};

	std::cout << "MANAGER ACCOUNT APPLICATION" << std::endl;

	while (true) {
		int choice = printMenu(mainMenu);
		if (choice == 1) {
			AccountEntity accountEntity = AccountEntity();
			accountService.createAcc(userName, password, confirmPass, fullName, dateOfBirth, gender, address, email, phoneNumber, accountEntity, isAdmin);
		}
		else if (choice == 2) {
			std::cout << "Dang nhap" << std::endl;
			std::cout << "Nhap ten tai khoan: ";
			std::cin >> userName;
			std::cout << "Nhap mat khau: ";
			std::cin >> password;

			if (!accountService.checkAccountLogin(userName, password)) {
				std::cout << "Dang nhap that bai." << std::endl;
				continue;
			}

			AccountEntity currentUser = accountService.getAccountByUserName(userName);
			bool isLogin = true;
			int accountId = currentUser.getId();
			int accountEditId;

			while (isLogin) {
				int menuChoice = currentUser.getIsAdmin() ? printMenu(mainMenuAdmin) : printMenu(mainMenuUser);

				switch (menuChoice) {
				case 1:
					if (currentUser.getIsAdmin()) {
						accountService.exportAccountsToCSV();
					}
					else {
						accountService.printAccount(userName);
					}
					break;

				case 2:
					accountService.updatePassWord(currentUser);
					break;

				case 3:
					accountService.updateAccountPersonal(fullName, dateOfBirth, gender, address, phoneNumber, email, accountId);
					break;

				case 4:
					if (currentUser.getIsAdmin()) {
						std::cout << "Nhap ten tai khoan user: ";
						std::cin >> userName;
						AccountEntity userToEdit = accountService.getAccountByUserName(userName);

						if (userToEdit.getUserName().empty()) {
							std::cout << "Khong tim thay tai khoan." << std::endl;
						}
						else {
							accountEditId = userToEdit.getId();
							accountService.updateAccountPersonal(fullName, dateOfBirth, gender, address, phoneNumber, email, accountEditId);
						}
					}
					else {
						handleWalletMenu(accountService, currentUser.getId(), mainMenuWallet, mainMenuWalletDetail);
					}
					break;

				case 5:
					if (currentUser.getIsAdmin()) {
						handleWalletMenu(accountService, currentUser.getId(), mainMenuWallet, mainMenuWalletDetail);
					}
					else {
						isLogin = false;  // Dang xuat
					}
					break;

				case 6:
					if (currentUser.getIsAdmin()) {
						isLogin = false;
					}
					else {
						return 0;
					}
					break;

				case 7:
					if (currentUser.getIsAdmin()) return 0;
					break;

				default:
					std::cout << "Lua chon khong phu hop." << std::endl;
					break;
				}
			}
		}
		else if (choice == 3) {
			return 0;
		}
		else {
			std::cout << "Lua chon khong phu hop." << std::endl;
		}
	}

	return 0;
}

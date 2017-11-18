/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Account.cpp
 * Author: zoltan
 * 
 * Created on November 17, 2017, 6:13 PM
 */

#include "Account.h"

Account::Account(double value, int accountNumber, string accountHolder) {
    this->amount = amount;
    this->accountNumber = accountNumber;
    this->accountHolder = accountHolder;
}

void Account::setAccountHolder(string accountHolder) {
    this->accountHolder = accountHolder;
}

string Account::getAccountHolder() const {
    return accountHolder;
}

void Account::setAccountNumber(int accountNumber) {
    this->accountNumber = accountNumber;
}

int Account::getAccountNumber() const {
    return accountNumber;
}

void Account::setAmount(double amount) {
    this->amount = amount;
}

double Account::getAmount() const {
    return amount;
}

int Tobj::getVersion(){
    return versionNumber;
}




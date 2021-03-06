int ebc(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "test.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (size_t i = 0; i < imageVec.size(); i++) {
    for (size_t j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }

  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  for (int i = 0; i < 786432; i++) {
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }
    i = i + 7;
    IntToBit(tempStrBit, tempInt, 64); // plaintext bits
    Des_Run_Bit(tempStrBit, tempStrBit, ENCRYPT);
    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempStrBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
  }

  int m = 0;
  for (size_t i = 0; i < imageVec.size(); i++) {
    for (size_t j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "ebc.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int ebc_decrypt(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "ebc.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (size_t i = 0; i < imageVec.size(); i++) {
    for (size_t j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }

  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，
  for (int i = 0; i < 786432; i++) {
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }

    IntToBit(tempStrBit, tempInt, 64); // plaintext bits
    Des_Run_Bit(tempStrBit, tempStrBit, DECRYPT);
    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempStrBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 7;
  }

  int m = 0;
  for (size_t i = 0; i < imageVec.size(); i++) {
    for (size_t j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "ebc_decrypt.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int cbc(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "test.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (size_t i = 0; i < imageVec.size(); i++) {
    for (size_t j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }

  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  bool tempPlainTextBit[64]; //明文bits
  for (int i = 0; i < 786432; i++) {
    // 转换明文为64位bit
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }
    IntToBit(tempPlainTextBit, tempInt, 64); // plaintext bits

    // xor明文与IV或与密文，64位
    if (i == 0) {
      Xor(tempPlainTextBit, IV, 64);
    } else {
      Xor(tempPlainTextBit, tempStrBit, 64);
    }

    // 加密异或操作后的 64 bits
    Des_Run_Bit(tempStrBit, tempPlainTextBit, ENCRYPT);

    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempStrBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 7;
  }

  int m = 0;
  for (size_t i = 0; i < imageVec.size(); i++) {
    for (size_t j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "cbc.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int cbc_decrypt(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "cbc.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }

  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  bool tempOldPlainTextBit[64]; // 上一次的明文bits
  bool tempPlainTextBit[64];    //明文bits
  for (int i = 0; i < 786432; i++) {
    // 转换明文为64位bit
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }

    // plaintext bits
    IntToBit(tempPlainTextBit, tempInt, 64);

    // 解密 64 bits
    Des_Run_Bit(tempStrBit, tempPlainTextBit, DECRYPT); // ENCRYPT DECRYPT

    // xor明文与IV或与密文，64位
    if (i == 0) {
      Xor(tempStrBit, IV, 64);
    } else {
      Xor(tempStrBit, tempOldPlainTextBit, 64);
    }

    // plaintext bits
    IntToBit(tempOldPlainTextBit, tempInt, 64);

    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempStrBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 7;
  }

  int m = 0;
  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "cbc_decrypt.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int ofb(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "test.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }
  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  bool tempPlainTextBit[64]; //明文bits
  for (int i = 0; i < 786432;) {
    // 不断重新获得加密后IV
    if (i == 0) {
      Des_Run_Bit(tempStrBit, IV, ENCRYPT);
    } else {
      Des_Run_Bit(tempStrBit, tempStrBit, ENCRYPT);
    }

    // 开始处理明文
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }
    IntToBit(tempPlainTextBit, tempInt, 64); // plaintext bits
    Xor(tempPlainTextBit, tempStrBit, 64);
    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempPlainTextBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 8;
  }

  int m = 0;
  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "ofb.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int ofb_decrypt(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "ofb.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }
  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  bool tempPlainTextBit[64]; //明文bits
  for (int i = 0; i < 786432;) {
    // 不断重新获得加密后IV
    if (i == 0) {
      Des_Run_Bit(tempStrBit, IV, ENCRYPT);
    } else {
      Des_Run_Bit(tempStrBit, tempStrBit, ENCRYPT);
    }

    // 开始处理明文
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }
    IntToBit(tempPlainTextBit, tempInt, 64); // plaintext bits
    Xor(tempPlainTextBit, tempStrBit, 64);
    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempPlainTextBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 8;
  }

  int m = 0;
  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "ofb_decrypt.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int ctr(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "test.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }
  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  bool tempIV[64] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                     1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                     1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                     1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1};
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  bool tempPlainTextBit[64]; //明文bits
  for (int i = 0; i < 786432;) {

    // // 不断重新获得加密后IV
    if (i == 0) {
      Des_Run_Bit(tempStrBit, tempIV, ENCRYPT);
    } else {
      add1(tempIV, tempIV);
      Des_Run_Bit(tempStrBit, tempStrBit, ENCRYPT);
    }

    // 开始处理明文
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }
    IntToBit(tempPlainTextBit, tempInt, 64); // plaintext bits
    Xor(tempPlainTextBit, tempStrBit, 64);
    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempPlainTextBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 8;
  }

  int m = 0;
  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "ctr.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

int ctr_decrypt(bool key[]) {
  vector<vector<Color>> imageVec(sizey, vector<Color>(sizex));
  if (!bmpRead(imageVec, "ctr.bmp")) {
    cout << "Read image error!!" << endl;
    return -1;
  }

  int str[786432];
  vector<int> temp;

  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      temp.push_back(imageVec[i][j].R);
      temp.push_back(imageVec[i][j].G);
      temp.push_back(imageVec[i][j].B);
    }
  }
  for (int i = 0; i < temp.size(); i++) {
    str[i] = temp[i];
  }

  Des_SetKey(key);
  bool tempIV[64] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                     1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                     1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                     1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1};
  std::vector<int> resultV;
  int tempInt[8];
  bool tempStrBit[64]; //要被加密的数据，开始是IV，后来是IV每次加密后结果
  bool tempPlainTextBit[64]; //明文bits
  for (int i = 0; i < 786432;) {

    // // 不断重新获得加密后IV
    if (i == 0) {
      Des_Run_Bit(tempStrBit, tempIV, ENCRYPT);
    } else {
      add1(tempIV, tempIV);
      Des_Run_Bit(tempStrBit, tempStrBit, ENCRYPT);
    }

    // 开始处理明文
    for (int j = 0; j < 8; j++) {
      tempInt[j] = str[i + j];
    }
    IntToBit(tempPlainTextBit, tempInt, 64); // plaintext bits
    Xor(tempPlainTextBit, tempStrBit, 64);
    int tempOutInt[8]; // 密文
    boolArrayToInt(tempOutInt, tempPlainTextBit);
    for (int j = 0; j < 8; j++) {
      resultV.push_back(tempOutInt[j]);
    }
    i = i + 8;
  }

  int m = 0;
  for (int i = 0; i < imageVec.size(); i++) {
    for (int j = 0; j < imageVec[i].size(); j++) {
      imageVec[i][j].R = resultV[m];
      imageVec[i][j].G = resultV[m + 1];
      imageVec[i][j].B = resultV[m + 2];
      m = m + 3;
    }
  }

  if (!bmpWrite(imageVec, "ctr_decrypt.bmp")) {
    cout << "Write image error!!" << endl;
    return -1;
  }
}

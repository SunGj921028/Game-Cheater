# Game-Cheater

## 針對DOS的金庸群俠傳遊戲開發的遊戲作弊器

### Environment Set
1. 請在Linux或WSL系統底下下gcc編譯此程式
2. 請將遊戲紀錄檔(如R1.GRP)丟到同目錄底下去執行

### 可調整的內容
1. 所學武功及等級
2. 所帶物品及數量
3. 角色能力數值

![image](https://github.com/SunGj921028/Game-Cheater/blob/main/sceen.png)

#### 特殊提醒
#### <功夫>
1. 可以將目前有的功夫(代碼,等級)條列出來，及時更新
2. 可以新增功夫(代碼,等級)，不能超過10個
3. 查看功夫後才會得知現在有幾個功夫(才可以進行判錯)
4. 因為我認為功夫學習後就是一輩子了，所以沒有製作刪除功夫的功能
5. 不同功夫可以重複休習，但請合理的使用此外掛(看一下我給的表)

#### <物品>
1. 上限200
2. 物品數量0-9999
3. 可以查看物品的內容(代碼,數量)，及時更新
4. 查看後會得知現在有的物品數量以作判斷
5. 可以新增物品(代碼,數量)
6. 同樣的物品可以塞在不同的物品欄(這非常符合邏輯)
7. 可以刪除物品(需輸入想要刪除哪一項物品)，刪除是直接變FF 00
8. 修練物品沒有提供修改功能(請自行修練)

#### <能力>
1. 可修改20種會顯示在遊戲介面的能力
2. 每個能力範圍0-999(經驗0-60000)
3. 從(1-20)選擇想更改的東西，可以直接在沒有武器防具的情況下裝上裝備
4. 每次更改會重新顯示能力表
5. 因穿上裝備後的能力值會被修改(功防輕功)，但我沒有查到增加的能力值是多少
  所以在顯示能力值的表中，顯示的是未穿裝備的能力狀態
6.更改能力後可選擇是否要學習左右互博和是否要更改角色素質(0-100)

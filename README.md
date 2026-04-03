# Aluakernel

---

#問題：

為什麼我啟動時會出現:note : Target RIP: 0x000000007DD59080 ?

> 因為系統會預先計算可能會出事的點，讓我更好診斷內核故障的點

原始碼會公布嗎？

> 不確定，可能不會公開，也可能會公開

引導系統基於？

> picoefi

內核是從零嗎？

> 對

如果啟動後出現亂碼怎麼辦？
例:
![圖片](https://github.com/JW0521-X/Aluakernel/blob/main/gc.png)
> 嘗試重啟，可能是因為跑太快了導致反應來不及
---

這裡是啟動後的樣子:
https://github.com/JW0521-X/Aluakernel/blob/main/run.png

# Aluakernel

---

#問題：

為什麼我啟動時會出現:note : Target RIP: 0x............. ?

> 因為系統會預先計算可能會出事的點，讓我更好診斷內核故障的點

原始碼會公布嗎？

> 不確定，可能不會公開，也可能會公開

引導系統基於？

> picoefi

內核是從零嗎？

> 對

啟動後出現錯誤代碼怎麼辦？
例：![圖片](https://github.com/JW0521-X/Aluakernel/blob/main/error.png)

> 請到AluaH網站的錯誤代碼頁面，解決問題
>[AluaH code]([https://github.com/JW0521-X/Aluakernel/releases](https://jw0521-x.github.io/AluaH/AluaCode.html))

一直重啟怎麼辦？
> 建議告訴開發者，可能是因為那個版本的系統是壞掉的

如何試用？
>[預發布0.0.1](https://github.com/JW0521-X/Aluakernel/releases)下載AluaBootloader.efi和alua.bin


```bash
mkdir -p boot/EFI/BOOT
cp AluaBootloader.efi boot/EFI/BOOT/BOOTX64.EFI
cp ./alua.bin boot/
qemu-system-x86_64 -cpu max -M q35 -L . -pflash /path/to/pflash.fd -drive file=fat:rw:boot,format=raw
```
---

這裡是啟動後的樣子:
(0.0.1)
![圖片](https://github.com/JW0521-X/Aluakernel/blob/main/run.png)



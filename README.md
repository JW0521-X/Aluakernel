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
或:
![圖片](https://github.com/JW0521-X/Aluakernel/blob/main/gc2.png)
> 嘗試重啟，可能是因為跑太快了導致反應來不及

一直重啟怎麼辦？
> 建議告訴開發者，可能是因為那個版本的系統是壞掉的

如何試用？
>請進到![預發布0.0.1]下載AluaBootloader.efi和alua.bin
>
‘’‘
mkdir -p boot/EFI/BOOT
cp AluaBootloader.efi boot/EFI/BOOT/BOOTX64.EFI
cp ./alua.bin boot/
qemu-system-x86_64 -cpu max -M q35 -L . -pflash /path/to/pflash.fd -drive file=fat:rw:boot,format=raw
‘’‘
---

這裡是啟動後的樣子:
(0.0.1)
![圖片](https://github.com/JW0521-X/Aluakernel/blob/main/run.png)
(0.0.2)
![圖片](https://github.com/JW0521-X/Aluakernel/blob/main/run2.png)


//cheat editor created by SunGj
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
//header file
void print_status(FILE *fp);
void print_kf(FILE *fp);
void print_item(FILE *fp);

int32_t print_option(){
    int32_t cho = 0;
    printf("選項為:\n");
    printf("0.退出\n");
    printf("1.變更功夫\n");
    printf("2.變更物品\n");
    printf("3.變更能力\n");
    printf("請選擇想要執行的操作(0-3): ");
    scanf("%d",&cho);
    return cho;
}

long hex_to_int(int32_t a, int32_t b){
    char n[12] = {0};
    long ret = 0;
    int32_t c = (a << 8) | b;
    sprintf(n,"%d",c);
    ret = strtol(n,NULL,10);
    return ret;
}

int32_t count_remain = 0;
void kf(FILE *fp){
    int32_t way = 0;
    printf("----------------------------><\n");
    printf("輸入0返回初始頁面或輸入1繼續操作: ");
    scanf("%d",&way);
    if(way!=0&&way!=1){
        printf("Invalid Input!\n");
        return;
    }
    if(way==0) return;
    fseek(fp,962,SEEK_SET);
    printf("----------------------\n");
    printf("第一次使用請先查看現有的功夫!!\n");
    printf("1.查看目前已有的功夫\n");
    printf("2.新增功夫\n");
    printf("請選擇要執行的行動(1-2): ");
    int32_t cho = 0;
    scanf("%d",&cho);
    if(cho!=1&&cho!=2&&cho!=3){
        printf("Invalid Input!\n");
        return;
    }
    if(cho==1){
        int32_t count_num = 1;
        int32_t kf = 0;
        int32_t n = 0;
        int32_t n2 = 0;
        int32_t lv = 0;
        long ans = 0;
        printf("------------------------------><\n");
        printf("功夫格數    功夫代碼     等級\n");
        printf("------------------------------><\n");
        int32_t count = 1;
        count_remain = 0;
        while(count<=10){
            fread(&kf,sizeof(uint8_t),2,fp);
            fseek(fp,19,SEEK_CUR);
            fread(&n,sizeof(uint8_t),1,fp);
            fseek(fp,-2,SEEK_CUR);
            fread(&n2,sizeof(uint8_t),1,fp);
            ans = hex_to_int(n,n2);
            if(ans<=99&&ans>=0){
                lv = 1;
            }else if(ans<=199){
                lv = 2;
            }else if(ans<=299){
                lv = 3;
            }else if(ans<=399){
                lv = 4;
            }else if(ans<=499){
                lv = 5;
            }else if(ans<=599){
                lv = 6;
            }else if(ans<=699){
                lv = 7;
            }else if(ans<=799){
                lv = 8;
            }else if(ans<=899){
                lv = 9;
            }else if(ans<=999){
                lv = 10;
            }
            if(kf!=0){
                if(count_num!=10){
                    printf("    %d.         %02X        lv. %d\n",count_num,kf,lv);
                }else{
                    printf("   %d.         %02X        lv. %d\n",count_num,kf,lv);
                }
                count_remain++;
            }
            count_num++;
            fseek(fp,-19,SEEK_CUR);
            count++;
        }
        printf("-----------------><\n");
        printf("剩餘可新增項數為%d項\n",10-count_remain);
    }else if(cho==2){
        printf("請輸入想新增的功夫(01 ~ 5C): ");
        char x[5] = {0};
        scanf("%s",x);
        int32_t y = strtol(x, NULL, 16);
        if(y<1||y>92){
            printf("Wrong Input!\n");
            return;
        }

        int32_t lv = 0;
        printf("請輸入想要學習的功夫等級(1 ~ 10): ");
        scanf("%d",&lv);
        if(lv<1||lv>10){
            printf("Wrong Input!\n");
            return;
        }
        if(count_remain>=10){
            printf("Not enough space for kf!\n");
            return;
        }
        printf("新增代碼為%s且等級為%d的功夫完成!!\n",x,lv);

        int32_t count_bytes = 1;
        while(count_bytes<=10){
            int32_t is_kf = 0;
            fread(&is_kf,sizeof(uint8_t)*2,1,fp);
            if(is_kf==0){
                fseek(fp,-2,SEEK_CUR);
                fwrite(&y,sizeof(uint8_t),1,fp);
                break;
            }
            count_bytes++;
        }
        int32_t temp = count_bytes;
        count_bytes = 1;
        fseek(fp,982,SEEK_SET);
        while(count_bytes<=10){
            int32_t is_lv = 0;
            uint16_t val = 0;
            fread(&is_lv,sizeof(uint8_t),2,fp);
            if(count_bytes==temp){
                fseek(fp,-2,SEEK_CUR);
                if(lv==1){
                    val = 0;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==2){
                    val = 100;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==3){
                    val = 200;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==4){
                    val = 300;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==5){
                    val = 400;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==6){
                    val = 500;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==7){
                    val = 600;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==8){
                    val = 700;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==9){
                    val = 800;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }else if(lv==10){
                    val = 900;
                    fwrite(&val,sizeof(uint16_t),1,fp);
                }
                break;
            }
            count_bytes++;
        }
    }/*else if(cho==3){
        printf("請輸入想要移除的功夫的項數: ");
        int32_t cho = 0;
        scanf("%d",&cho);
        if(cho>10||cho<1){
            printf("Invalid Input!\n");
            return;
        }
        int32_t count = 1;
        int32_t count_byte = 1;
        int32_t n = 0;
        while(count_byte<=10){
            if(count==cho){
                fwrite(&n,sizeof(uint8_t),1,fp);
                fseek(fp,-1,SEEK_CUR);
            }
            fseek(fp,2,SEEK_CUR);
            count++;
            count_byte++;
        }
        fseek(fp,982,SEEK_SET);
        count_byte = 1;
        count = 1;
        while(count_byte<=10){
            if(cho==count){
                fwrite(&n,sizeof(uint8_t),1,fp);
                fseek(fp,1,SEEK_CUR);
                fwrite(&n,sizeof(uint8_t),1,fp);
            }
            count++;
            count_byte++;
        }
        return;
    }*/
    print_kf(fp);
    return;
}

void print_kf(FILE *fp){
    printf("-------------------------------------------------><\n");
    printf("01野球拳     02武當長拳   03羅漢拳     04靈蛇拳\n");
    printf("05神王毒掌   06七傷拳     07混元拳     08寒冰綿掌\n");
    printf("09鷹爪功     0A逍遙掌     0B鐵掌       0C幻陰指\n");
    printf("0D寒冰神掌   0E千手如來掌 0F天山六陽掌 10玄冥神掌\n");
    printf("11冰蠶毒掌   12龍象般若功 13一陽指     14太極拳\n");
    printf("15空明拳     16蛤蟆功     17太玄神功   18黯然銷魂掌\n");
    printf("19降龍十八掌 1A葵花神功   1B化功大法   1C吸星大法\n");
    printf("1D北冥神功   1E六脈神劍   1F躺屍劍法   20青城劍法\n");
    printf("21冰雪劍法   22恆山劍法   23泰山劍法   24衡山劍法\n");
    printf("25神龍劍法   26嵩山劍法   27全真劍法   28峨嵋劍法\n");
    printf("29武掌劍法   2A萬花劍法   2B潑墨劍法   2C雪山劍法\n");
    printf("2D泰山十八盤 2E迴峰落雁劍 2F兩儀劍法   30太岳三青峰\n");
    printf("31玉女素心劍 32逍遙劍法   33慕容劍法   34倚天劍法\n");
    printf("35七星劍法   36金蛇劍法   37苗家劍法   38玉蕭劍法\n");
    printf("39玄鐵劍法   3A太極劍法   3B達摩劍法   3C辟邪劍法\n");
    printf("3D獨孤九劍   3E西瓜刀法   3F血刀大法   40狂風刀法\n");
    printf("41反兩儀刀法 42火燄刀法   43胡家刀法   44霹靂刀法\n");
    printf("45神龍雙勾   46大輪杖法   47怪異武器   48鍊心彈\n");
    printf("49叫化棍法   4A火燄發射器 4B鱷魚       4C大蜘珠\n");
    printf("4D毒龍鞭法   4E黃沙萬里鞭 4F雪怪       50判官筆\n");
    printf("51持棋盤     52大剪刀     53持瑤琴     54大蟒蛇\n");
    printf("55金花杖法   56神龍鹿杖   57打拘棍法   58五輪大法\n");
    printf("59松風劍法   5A普通攻擊   5B獅子吼     5C九陽神功\n");
    printf("-------------------------------------------------><\n");
    kf(fp);
    return;
}

void nineninenine(FILE *fp, int32_t offset){
    int32_t stat = 0;
    printf("請輸入想要變更的數值(0~999): ");
    scanf("%d",&stat);
    if(stat>999||stat<0){
        printf("Invalid Input!\n");
        return;
    }
    if(offset!=0){
        fseek(fp,offset,SEEK_CUR);
    }
    fwrite(&stat,sizeof(uint8_t),2,fp);
    return;
}

void attack(FILE *fp){
    char cho[5] = {0};
    printf("-------------------------------------------------><\n");
    printf("\033[34m武器列表\033[0m-->\n");
    printf("6A玄鐵劍      6B君子劍      6C淑女劍      6D倚天劍      6E金蛇劍\n");
    printf("6F凝碧劍      70白龍劍      71白虹劍      72周公劍      73血刀\n");
    printf("74冷月寶刀    75屠龍刀      76綠波香露刀  77霹靂狂刀    C0真武劍\n");
    printf("請選擇你要裝備上的武器: ");
    scanf("%s",cho);
    int32_t x = strtol(cho,NULL,16);
    if(x!=192){
        if(x<106||x>119){
            printf("Invalid Input!\n");
            return;
        }
    }
    printf("-------------------------------------------------><\n");
    fwrite(&x,sizeof(uint8_t),1,fp);
    x = 0;
    fwrite(&x,sizeof(uint8_t),1,fp);
    return;
}

void defence(FILE *fp){
    char cho[5] = {0};
    printf("-------------------------------------------------><\n");
    printf("\033[35m防具列表\033[0m-->\n");
    printf("78軟蝟甲      79金絲背心        7A烏蠶衣      7B鱷魚皮甲        C5皮衣\n");
    printf("請選擇你要裝備上的防具: ");
    scanf("%s",cho);
    int32_t x = strtol(cho,NULL,16);
    if(x!=197){
        if(x<120||x>123){
            printf("Invalid Input!\n");
            return;
        }
    }
    printf("-------------------------------------------------><\n");
    fwrite(&x,sizeof(uint8_t),1,fp);
    x = 0;
    fwrite(&x,sizeof(uint8_t),1,fp);
    return;
}

void status(FILE *fp){
    int32_t way = 0;
    int32_t cho = 0;
    int32_t stat = 0;
    printf("----------------------------><\n");
    printf("輸入0返回初始頁面或輸入1繼續操作: ");
    scanf("%d",&way);
    if(way==0) return;
    if(way!=0&&way!=1){
        printf("Invalid Input!\n");
        return;
    }
    printf("請選擇需要修改的能力值(1-20): ");
    scanf("%d",&cho);
    if(cho>20||cho<1){
        printf("Invalid Input!\n");
        return;
    }
    if((cho<8&&cho!=5&&cho!=6)||(cho==19||cho==20)){
        fseek(fp,866,SEEK_SET);
    }else{
        fseek(fp,918,SEEK_SET);
    }
    switch(cho){
        case 1:
            nineninenine(fp,0);
            break;
        case 2:
            printf("請輸入想要變更的數值(1~60000): ");
            scanf("%d",&stat);
            if(stat>60000||stat<0){
                printf("Invalid Input!\n");
                return;
            }
            fseek(fp,2,SEEK_CUR);
            fwrite(&stat,sizeof(uint8_t),2,fp);
            break;
        case 3:
            nineninenine(fp,4);
            break;
        case 4:
            nineninenine(fp,6);
            break;
        case 5:
            nineninenine(fp,0);
            break;
        case 6:
            nineninenine(fp,2);
            break;
        case 7:
            nineninenine(fp,12);
            break;
        case 8:
            nineninenine(fp,4);
            break;
        case 9:
            nineninenine(fp,6);
            break;
        case 10:
            nineninenine(fp,8);
            break;
        case 11:
            nineninenine(fp,10);
            break;
        case 12:
            nineninenine(fp,12);
            break;
        case 13:
            nineninenine(fp,14);
            break;
        case 14:
            nineninenine(fp,18);
            break;
        case 15:
            nineninenine(fp,20);
            break;
        case 16:
            nineninenine(fp,22);
            break;
        case 17:
            nineninenine(fp,24);
            break;
        case 18:
            nineninenine(fp,26);
            break;
        case 19:
            fseek(fp,16,SEEK_CUR);
            attack(fp);
            break;
        case 20:
            fseek(fp,18,SEEK_CUR);
            defence(fp);
            break;
        default:
            printf("Wrong Input!\n");
            return;
    }
    int32_t other = 0;
    printf("是否要(1)修改左右互博或(2)資質\n");
    printf("0.不用, 1.左右, 2.資質\n");
    printf("請輸入:");
    scanf("%d",&other);
    if(other!=0&&other!=1&&other!=2){
        printf("Invalid Input!\n");
        return;
    }
    fseek(fp,918,SEEK_SET);
    if(other==1){
        fseek(fp,34,SEEK_CUR);
        int32_t lr = 0;
        printf("0.不會\n");
        printf("1.學會\n");
        printf("請輸入:");
        scanf("%d",&lr);
        if(lr!=0&&lr!=1){
            printf("Invalid Input!\n");
            return;
        }
        int32_t cool = 0;
        if(lr==0){
            fwrite(&cool,sizeof(uint8_t),2,fp);
        }else if(lr==1){
            cool = 1;
            fwrite(&cool,sizeof(uint8_t),2,fp);
        }
    }else if(other==2){
        int32_t brain = 0;
        fseek(fp,38,SEEK_CUR);
        printf("請輸入想要的資質(0-100): ");
        scanf("%d",&brain);
        if(brain<0||brain>100){
            printf("Invalid Input!\n");
            return;
        }
        fwrite(&brain,sizeof(uint8_t),2,fp);
    }
    print_status(fp);
    return;
}

void print_status(FILE *fp){
    fseek(fp,866,SEEK_SET);
    long data[21] = {0};
    long temp = 0;
    int32_t count = 1;
    int32_t count_data = 0;
    int32_t n = 0;
    int32_t n2 = 0;
    while(count<=7){
        if(count==5){
            fseek(fp,4,SEEK_CUR);
        }else if(count==6){
            fseek(fp,2,SEEK_CUR);
        }
        fseek(fp,1,SEEK_CUR);
        fread(&n,sizeof(uint8_t),1,fp);
        fseek(fp,-2,SEEK_CUR);
        fread(&n2,sizeof(uint8_t),1,fp);
        fseek(fp,1,SEEK_CUR);
        temp = hex_to_int(n,n2);
        data[count_data++] = temp;
        count++;
    }
    fseek(fp,918,SEEK_SET);
    count = 1;
    n = 0;
    n2 = 0;
    temp = 0;
    while(count<=14){
        fseek(fp,1,SEEK_CUR);
        fread(&n,sizeof(uint8_t),1,fp);
        fseek(fp,-2,SEEK_CUR);
        fread(&n2,sizeof(uint8_t),1,fp);
        //printf("%x %x\n",n,n2);
        fseek(fp,1,SEEK_CUR);
        temp = hex_to_int(n,n2);
        data[count_data++] = temp;
        count++;
    }
    printf("下面為裸裝時的能力值(不含武器防具)!!\n");
    printf("-------------------------------------------------><\n");
    printf("        能力      數值 ||         能力       數值\n");
    printf("-------------------------------------------------><\n");
    printf(" 1.     等級%10ld || 8.     攻擊力%10ld\n",data[0],data[9]);
    printf(" 2.     經驗%10ld || 9.      輕功%11ld\n",data[1],data[10]);
    printf(" 3. 現在生命%10ld || 10.    防禦力%10ld\n",data[2],data[11]);
    printf(" 4. 生命上限%10ld || 11.   醫療能力%9ld\n",data[3],data[12]);
    printf(" 5. 現在內力%10ld || 12.   用毒能力%9ld\n",data[7],data[13]);
    printf(" 6. 內力上限%10ld || 13.   解毒能力%9ld\n",data[8],data[14]);
    printf(" 7.     體力%10ld || 14.   拳掌能力%9ld\n",data[4],data[16]);
    printf("                       || 15.   御劍能力%9ld\n",data[17]);
    printf("                       || 16.   耍刀能力%9ld\n",data[18]);
    printf("                       || 17.   特殊兵器%9ld\n",data[19]);
    printf("                       || 18.   暗器技巧%9ld\n",data[20]);
    printf("                       || 19.     武器%11lX\n",data[5]);
    printf("                       || 20.     防具%11lX\n",data[6]);
    printf("-------------------------------------------------><\n");
    status(fp);
    return;
}

int32_t count_true_item = 0;
void item_list(FILE *fp){
    fseek(fp,36,SEEK_SET);
    int32_t count = 1;
    count_true_item = 0;
    int32_t count_four_bytes = 1;
    int32_t i = 0;
    int32_t n = 0;
    int32_t n2 = 0;
    long a = 0;
    printf("-------------------------------------------------><\n");
    printf("       代碼    數量\n");
    while(count_four_bytes<=200){
        fread(&i,sizeof(uint8_t),1,fp);
        fseek(fp,2,SEEK_CUR);
        fread(&n,sizeof(uint8_t),1,fp);
        fseek(fp,-2,SEEK_CUR);
        fread(&n2,sizeof(uint8_t),1,fp);
        a = hex_to_int(n,n2);
        if(i!=255){
            count_true_item++;
            printf("%3d.   %02X     %4ld\n",count,i,a);
        }
        count++;
        fseek(fp,1,SEEK_CUR);
        count_four_bytes++;
    }
    printf("共%d項物品(剩餘%d項可新增)\n",count_true_item,200-count_true_item);
    printf("-------------------------------------------------><\n");
    return;
}

void item(FILE *fp){
    fseek(fp,36,SEEK_SET);
    printf("如果是第一次使用請先查看物品清單!!\n");
    printf("1: 查看物品清單\n");
    printf("2: 新增物品內容\n");
    printf("3: 刪除物品內容\n");
    printf("請輸入想要執行的動作(1 or 2 or 3): ");
    int32_t cho = 0;
    scanf("%d",&cho);
    if(cho!=1&&cho!=2&&cho!=3){
        printf("Invalid Input!\n");
        return;
    }
    printf("-----------------------------------><\n");
    if(cho==1){
        item_list(fp);
    }else if(cho==2){
        if(count_true_item>=200){
            printf("Over 200 items!!\n");
            return;
        }
        int32_t s = 0;
        char hex[3] = {0};
        printf("請輸入你要新增的物品(輸入上面列表的代碼): ");
        scanf("%s",hex);
        printf("請輸入要新增的物品數量(1-9999): ");
        scanf("%d",&s);
        if(s<1||s>9999){
            printf("Invalid Input!\n");
            return;
        }
        int32_t hex_n = 0;
        int32_t i = 0;
        int32_t n = 0;
        int32_t n2 = 0;
        hex_n = strtol(hex,NULL,16);
        if(hex_n<0||hex_n>200){
            printf("Invalid Input!\n");
            return;
        }
        int32_t count_four_byte = 1;
        int32_t count = 1;
        while(count_four_byte<=200){
            fread(&i,sizeof(uint8_t),1,fp);
            if(i==255){
                fseek(fp,-1,SEEK_CUR);
                fwrite(&hex_n,sizeof(uint8_t),1,fp);
                fwrite(&n,sizeof(uint8_t),1,fp);
                fwrite(&s,sizeof(uint8_t),2,fp);
                break;
            }
            count_four_byte++;
        }
    }else if(cho==3){
        printf("請輸入想要刪除的物品的項目(第幾個)(請先查看物品清單): ");
        int32_t ic = 0;
        int32_t c = 0;
        scanf("%d",&ic);
        int32_t cb = 1;
        int32_t x = 0;
        int32_t t = 0;
        while(cb<=200){
            fread(&x,sizeof(uint8_t),1,fp);
            if(x!=255){
                c++;
            }
            if(c==ic){
                fseek(fp,-1,SEEK_CUR);
                t = 255;
                fwrite(&t,sizeof(uint8_t),1,fp);
                fwrite(&t,sizeof(uint8_t),1,fp);
                t = 0;
                fwrite(&t,sizeof(uint8_t),1,fp);
                fwrite(&t,sizeof(uint8_t),1,fp);
                break;
            }
            fseek(fp,3,SEEK_CUR);
            cb++;
        }
    }
    print_item(fp);
    return;
}

void print_item(FILE *fp){
    int32_t way = 0;
    printf("-----------------------------------><\n");
    printf("輸入0返回初始頁面或輸入1繼續操作: ");
    scanf("%d",&way);
    if(way!=0&&way!=1){
        printf("Invalid Input!\n");
        return;
    }
    if(way==0) return;
    printf("---------------------------------------------------------------------------><\n");
    printf("\033[31m道具\033[0m:\n");
    printf("00康貝特       01精氣丸        02白嵐氏雞精     03小還丹         04玉洞黑石丹\n");
    printf("05玉真散       06三黃寶臘丹    07玉靈散         08天香斷續膠     09黑玉斷續膏\n");
    printf("0A金牛運功散   0B人蔘          0C白雲熊膽丸     0D九花玉露丸     0E九轉靈寶丸\n");
    printf("0F田七鯊膽散   10九轉熊蛇丸    11無常丹         12鎮心理氣丸     13生生造化丹\n");
    printf("14天王保命丹   15寶濟丸        16黃蓮解毒丸     17天心解毒丹     18回陽五龍膏\n");
    printf("19牛黃血竭丹   1A六陽正氣丹    1B朱晴冰蟾       1C伏苓首烏丸     1D千年靈芝\n");
    printf("1E蛇膽         1F玉寶花蜜酒    20臘八粥         21大蟠桃         22千年人蔘\n");
    printf("23天山雪蓮     24通犀地龍丸    25千年冰蠶       26莽牯朱蛤       C4檳榔\n");
    printf("AB藥材         AC硝石          AE銀兩\n");
    printf("---------------------------------------------------------------------------><\n");
    printf("\033[32m武功秘笈\033[0m:\n");
    printf("27紫霞秘笈     28小無相功      29十八泥偶       2A神照經         2B易筋經\n");
    printf("2C洗髓經       2D梯雲縱心法    2E神行百變       2F凌波微步       30子午針灸經\n");
    printf("31華陀內昭圖   32胡青牛醫書    33五毒秘笈       34毒經           35藥王神篇\n");
    printf("36鐵掌拳譜     37七傷拳譜      38天山六陽掌     39玄冥神掌       3A太極拳經\n");
    printf("3B龍象般若功   3C太玄經        3D黯然消魂掌     3E降龍十八掌     3F北冥神功\n");
    printf("40吸星大法     41神木王鼎      42六脈神劍譜     43松風劍譜       44泰山十八盤\n");
    printf("45迴峰落雁劍法 46七星劍譜      47兩儀劍法       48金蛇秘笈       4A苗人劍法\n");
    printf("49玉女素心劍法 4B太極劍法      4C達摩劍譜       4D玄鐵劍法       4E辟邪劍譜\n");
    printf("4F獨孤九劍     50血刀經        51火燄刀法       52反兩儀刀法     53狂風刀法\n");
    printf("54胡家刀法     55霹靂刀法      56毒龍鞭法       58滿天花雨       59霹靂秘笈\n");
    printf("57黃沙萬里鞭法 5A含沙射影      5C乾坤大挪移     5D葵花寶典       5E九陰真經\n");
    printf("5B左右互搏之術 5F九陽真經\n");
    printf("---------------------------------------------------------------------------><\n");
    printf("\033[33m暗器\033[0m:\n");
    printf("60飛蝗石           61金錢鏢      62飛刀           63菩提子         64金蛇錐\n");
    printf("65霹靂彈           66毒蒺黎      67玉蜂針         68冰魄銀針       69黑血神針\n");
    printf("---------------------------------------------------------------------------><\n");
    printf("\033[34m武器列表\033[0m:\n");
    printf("6A玄鐵劍      6B君子劍      6C淑女劍      6D倚天劍      6E金蛇劍\n");
    printf("6F凝碧劍      70白龍劍      71白虹劍      72周公劍      73血刀\n");
    printf("74冷月寶刀    75屠龍刀      76綠波香露刀  77霹靂狂刀    C0真武劍\n");
    printf("---------------------------------------------------------------------------><\n");
    printf("\033[35m防具列表\033[0m:\n");
    printf("78軟蝟甲      79金絲背心        7A烏蠶衣      7B鱷魚皮甲        C5皮衣\n");
    printf("---------------------------------------------------------------------------><\n");
    printf("\033[36m劇情道具\033[0m:\n");
    printf("7C玉蜂漿           7D黑木令牌    7E梨花酒         7F翡翠杯         80七寶指環\n");
    printf("81神仙美女圖       82大燕國玉璽  84賞善罰惡令     85兩頁刀法       86斷腸草\n");
    printf("83大燕皇帝世系圖表 87闖王軍刀    88玄冰碧火酒     8A羊羔坐臀       8B小牛腰子\n");
    printf("89苗人鳳眼毒解藥   8C小豬耳朵    8D獐腿肉         8E兔肉           8F神杖\n");
    printf("90飛狐外傳         91雪山飛狐    92連城訣         93天龍八部       94射鵰英雄傳\n");
    printf("95白馬嘯西風       96鹿鼎記      97笑傲江湖       98書劍恩仇錄     99神鵰俠侶\n");
    printf("9A俠客行           9B倚天屠龍記  9C碧血劍         9D鴛鴦刀         9E七心海棠\n");
    printf("9F可蘭經           A0唐詩選輯    A1紅鑰匙         A2橙鑰匙         A3黃鑰匙\n");
    printf("A4綠鑰匙           A5藍鑰匙      A6紫鑰匙         A7鐵鑰匙         A8銅鑰匙\n");
    printf("A9銀鑰匙           AA金鑰匙      AD一朵藍花       B2劉仲甫嘔血棋譜 AF闖王藏寶圖\n");
    printf("B1廣陵散琴曲       B3張旭率意帖  B0玉笛誰家聽落梅 B4谿山行旅圖     B5一撮金毛\n");
    printf("B6羅盤             B8手帕        B7帶頭大哥書信   B9林震南遺言     BA智慧果\n");
    printf("BB鴛刀             BC鴦刀        BD武林帖         BE明教鐵燄令     BF一顆頭顱\n");
    printf("C1金盆洗手帖       C2燒刀子      C3鐵鏟\n");
    printf("---------------------------------------------------------------------------><\n");
    item(fp);
    return;
}

int main(){
    printf("Please use UTF-8 to show the below message!!\n");
    printf("Please read README!!\n");
    printf("All these programs are supported by Chinese.\nIf you can't read Chinese, you need to use UTF-8 yourself or search online or ask me\n");
    printf("請選擇想要更改的存檔(1-3): ");
    int32_t mode = 0;
    char save_name[10] = {0};
    scanf("%d",&mode);
    if(mode<1||mode>3){
        printf("Invalid Input!\n");
        return -1;
    }
    sprintf(save_name,"R%d.GRP",mode);
    while(1){
        printf("----------------------------><\n");
        FILE *fp = NULL;
        if((fp = fopen(save_name,"r+"))==NULL){
            perror("Cannot open file!!\n");
            return -1;
        }
        int32_t cho = 0;
        cho = print_option();
        if(cho<0||cho>3){
            printf("Invalid Input!\n");
            return -1;
        }
        switch(cho){
            case 0:
                printf("Thanks for using '~'\n");
                return 0;
            case 1:
                print_kf(fp);
                break;
            case 2:
                print_item(fp);
                break;
            case 3:
                print_status(fp);
                break;
            default:
                printf("Invalid Input!\n");
                return -1;
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void pass() {
	printf("按任意键继续...\n");
	getchar();
	getchar();
}
typedef struct equipment {
	char name[30];
	int hp;
	int atk;
	int def;
	int agi;
} eq;
typedef struct player {
	char name[20];	
	int level;
	int hp;
	int atk;
	int def;
	int agi;
	eq weapon;
	eq headarmor;
	eq bodyarmor;
	eq shoesarmor;
} pl;
typedef struct monster {
	char name[10];
	int hp;
	int atk;
} mon;
typedef struct save_data {
	pl gamer;
	int current_location;
	int monsters_defeated;
} save_data;
int save_game(save_data data) {
	FILE *file = fopen("game_save.dat", "wb");
	if (file == NULL) {
		printf("存档失败！\n");
		return 0;
	}
	fwrite(&data, sizeof(save_data), 1, file);
	fclose(file);
	printf("游戏已保存！\n");
	return 1;
}
int load_game(save_data *data) {
	FILE *file = fopen("game_save.dat", "rb");
	if (file == NULL) {
		printf("没有找到存档文件！\n");
		return 0;
	}
	fread(data, sizeof(save_data), 1, file);
	fclose(file);
	printf("游戏已加载！\n");
	return 1;
}
void show_player_status(pl gamer) {
	printf("\n=== 玩家状态 ===\n");
	printf("名字: %s\n等级: %d\n生命: %d\n攻击: %d\n防御: %d\n敏捷: %d\n", 
		gamer.name, gamer.level, gamer.hp, gamer.atk, gamer.def, gamer.agi);
	printf("================\n");
}
int main() {   
	srand(time(NULL));
	pl gamer;
	save_data game_data;
	int has_save = 0;
	printf("由于作者的游戏开发能力为一坨\n本游戏没有画面与音乐\n只是简单的文字演示\n");
	pass();
	printf("本作是很老套的勇者斗恶龙，最终目的是打败恶龙\n");
	pass();
	FILE *test_file = fopen("game_save.dat", "rb");
	if (test_file != NULL) {
		fclose(test_file);
		has_save = 1;
		printf("检测到存档文件！\n");
		printf("1. 开始新游戏\n2. 加载存档\n");
		int choice;
		scanf("%d", &choice);
		if (choice == 2) {
			if (load_game(&game_data)) {
				gamer = game_data.gamer;
				printf("欢迎回来，%s！\n", gamer.name);
				show_player_status(gamer);
				pass();				
				if (game_data.current_location == 1) {
					printf("继续森林冒险...\n");
					pass();
					goto forest_continue;
				} else if (game_data.current_location == 2) {
					printf("继续沙漠冒险...\n");
					pass();
					goto desert_continue;
				} else if (game_data.current_location == 3) {
					printf("准备挑战巨龙...\n");
					pass();
					goto dragon_fight;
				}
			}
		}
	}
	start1:
		printf("按1开始游戏,按2退出游戏\n按完1或2后，请再按一下回车\n");	
		int a;
		scanf("%d", &a);
		if (a == 2) return 0;
		if (a >= 3) {
			printf("无效选择,重新输入\n");
			goto start1;
		}
		printf("请输入你的名字\n");
		scanf("%s", gamer.name);
		gamer.level = 1;
		gamer.hp = 100;
		gamer.atk = 5;
		gamer.def = 0;
		gamer.agi = 5;
		show_player_status(gamer);
		pass();
		printf("选择你的职业\n1. 战士\n2. 游侠\n");
		int b;
		scanf("%d", &b);
		if (b == 1) {
			printf("获得装备：铁剑，铠甲，战靴\n");
			gamer.hp += 100;
			gamer.atk += 15;
			gamer.def += 20;
			gamer.agi += 10;
		} else if (b == 2) {
			printf("获得装备：长弓，皮甲，运动鞋\n");
			gamer.hp += 50;
			gamer.atk += 40;
			gamer.def += 10;
			gamer.agi += 50;
		}
		show_player_status(gamer);
		pass();
		game_data.gamer = gamer;
		game_data.monsters_defeated = 0;
		start2:
			printf("请选择你要去的地方\n1. 森林\n2. 沙漠\n3. 保存游戏\n");
			int c;
			scanf("%d", &c);
			if (c == 3) {
				game_data.current_location = 0; // 主菜单
				save_game(game_data);
				goto start2;
			}
			switch (c) {
			case 1:
				game_data.current_location = 1;
				goto flag1;
			case 2:
				game_data.current_location = 2;
				goto flag2;
			default:
				printf("无效选择,重新输入\n");
				goto start2;
			}
			flag1:
				printf("你行走在森林中\n");	
				pass();
				mon forest_monsters[4];
				strcpy(forest_monsters[0].name, "史莱姆");
				forest_monsters[0].hp = 50;
				forest_monsters[0].atk = 20;
				strcpy(forest_monsters[1].name, "哥布林");
				forest_monsters[1].hp = 100;
				forest_monsters[1].atk = 50;
				strcpy(forest_monsters[2].name, "石头人");
				forest_monsters[2].hp = 200;
				forest_monsters[2].atk = 100;
				strcpy(forest_monsters[3].name, "巨蝎子");
				forest_monsters[3].hp = 100;
				forest_monsters[3].atk = 20;
				forest_continue:
					for (int i = game_data.monsters_defeated; i < 3; i++) {
						printf("你遇到了%s\n战斗开始！\n", forest_monsters[i].name);	
						pass();
						game_data.monsters_defeated = i;
						game_data.current_location = 1;
						game_data.gamer = gamer;
						int initial_hp = gamer.hp;
						int round = 1;
						while (gamer.hp > 0 && forest_monsters[i].hp > 0) {
							printf("\n--- 第%d回合 ---\n", round);	
							pass();
							printf("战斗选项：1.继续战斗 2.保存游戏并退出\n");
							int fight_choice;
							scanf("%d", &fight_choice);
							if (fight_choice == 2) {
								save_game(game_data);
								printf("游戏已保存，下次可继续战斗！\n");
								return 0;
							}
							if (gamer.agi > rand() % 100) {
								forest_monsters[i].hp -= gamer.atk;
								printf("你先手攻击！\n");	
								pass();
								printf("%s受到了%d点伤害\n", forest_monsters[i].name, gamer.atk);	
								pass();
							} else {
								int damage = forest_monsters[i].atk - gamer.def;
								if (damage > 0) {
									gamer.hp -= damage;
									printf("%s先手攻击！\n", forest_monsters[i].name);	
									pass();
									printf("你受到了%d点伤害\n", damage);	
									pass();
								} else {
									printf("%s先手攻击！\n", forest_monsters[i].name);	
									pass();
									printf("你全防出去了，未受到伤害\n");	
									pass();
								}
								if (gamer.hp > 0) {
									forest_monsters[i].hp -= gamer.atk;
									printf("你反击！%s受到了%d点伤害\n", forest_monsters[i].name, gamer.atk);	
									pass();
								}
							}
							printf("你的生命: %d, %s的生命: %d\n", gamer.hp, forest_monsters[i].name, forest_monsters[i].hp);	
							pass();
							round++;
						}						
						printf("\n=== 战斗结束 ===\n");
						pass();	
						if (gamer.hp > 0) {
							printf("你打败了%s！\n", forest_monsters[i].name);	
							pass();
							gamer.level++;
							gamer.atk += 10;
							gamer.def += 5;
							gamer.hp = initial_hp + 125;
							gamer.agi += 5;							
							printf("你升级了\n");
							pass();
							show_player_status(gamer);							pass();
							game_data.monsters_defeated = i + 1;
							game_data.gamer = gamer;
						} else {
							printf("你被%s打败了！游戏结束\n胜败乃兵家常事，请少侠重新来过\n", forest_monsters[i].name);	
							pass();
							remove("game_save.dat");
							return 0;
						}
						printf("================\n\n");	
						pass();
					}					
					if (gamer.hp > 0) {
						printf("恭喜你,走出了森林!\n准备好迎接巨龙吧！\n");	
						pass();
						game_data.current_location = 3;
						game_data.monsters_defeated = 0;
					}
					goto flag3;	
					flag2:
						printf("你行走在沙漠中\n");	
						pass();						
						mon desert_monsters[3];
						strcpy(desert_monsters[0].name, "沙虫");
						desert_monsters[0].hp = 80;
						desert_monsters[0].atk = 30;
						strcpy(desert_monsters[1].name, "蝎子王");
						desert_monsters[1].hp = 120;
						desert_monsters[1].atk = 40;
						strcpy(desert_monsters[2].name, "木乃伊");
						desert_monsters[2].hp = 150;
						desert_monsters[2].atk = 35;						
						desert_continue:
							for (int i = game_data.monsters_defeated; i < 3; i++) {
								printf("你遇到了%s\n战斗开始！\n", desert_monsters[i].name);	
								pass();								
								game_data.monsters_defeated = i;
								game_data.current_location = 2;
								game_data.gamer = gamer;								
								int initial_hp = gamer.hp;
								int round = 1;								
								while (gamer.hp > 0 && desert_monsters[i].hp > 0) {
									printf("\n--- 第%d回合 ---\n", round);	
									pass();
									printf("战斗选项：1.继续战斗 2.保存游戏并退出\n");
									int fight_choice;
									scanf("%d", &fight_choice);
									if (fight_choice == 2) {
										save_game(game_data);
										printf("游戏已保存，下次可继续战斗！\n");
										return 0;
									}
									if (gamer.agi > rand() % 100) {
										desert_monsters[i].hp -= gamer.atk;
										printf("你先手攻击！\n");	
										pass();
										printf("%s受到了%d点伤害\n", desert_monsters[i].name, gamer.atk);	
										pass();
									} else {
										int damage = desert_monsters[i].atk - gamer.def;
										if (damage > 0) {
											gamer.hp -= damage;
											printf("%s先手攻击！\n", desert_monsters[i].name);	
											pass();
											printf("你受到了%d点伤害\n", damage);	
											pass();
											printf("你中毒了，受到了%d点中毒伤害\n", damage);	
											pass();
											gamer.hp -= i + 20;
										} else {
											printf("%s先手攻击！\n", desert_monsters[i].name);	
											pass();
											printf("你全防出去了，未受到伤害\n");	
											pass();
										}
										if (gamer.hp > 0) {
											desert_monsters[i].hp -= gamer.atk;
											printf("你反击！%s受到了%d点伤害\n", desert_monsters[i].name, gamer.atk);	
											pass();
										}
									}
									printf("你的生命: %d, %s的生命: %d\n", gamer.hp, desert_monsters[i].name, desert_monsters[i].hp);	
									pass();
									round++;
								}								
								printf("\n=== 战斗结束 ===\n");
								pass();								
								if (gamer.hp > 0) {
									printf("你打败了%s！\n", desert_monsters[i].name);	
									pass();
									gamer.level++;
									gamer.atk += 10;
									gamer.def += 5;
									gamer.hp = initial_hp + 125;
									gamer.agi += 5;									
									printf("你升级了\n");
									pass();
									show_player_status(gamer);
									pass();									
									game_data.monsters_defeated = i + 1;
									game_data.gamer = gamer;
								} else {
									printf("你被%s打败了！游戏结束\n胜败乃兵家常事，请少侠重新来过\n", desert_monsters[i].name);	
									pass();
									remove("game_save.dat");
									return 0;
								}
								printf("================\n\n");	
								pass();
							}							
							if (gamer.hp > 0) {
								printf("恭喜你,走出了沙漠!\n准备好迎接巨龙吧！\n");	
								pass();
								game_data.current_location = 3;
								game_data.monsters_defeated = 0;
							}							
							flag3:
								dragon_fight:
									printf("经过冒险，你终于来到了巨龙跟前\n");
									pass();									
									game_data.current_location = 3;
									save_game(game_data); // 最终战斗前自动保存									
									int player_hp = 3;  
									int dragon_hp = 3;  									
									while (player_hp > 0 && dragon_hp > 0) {
										int player_attack = rand() % 3;
										int dragon_attack = rand() % 3;										
										if (player_attack > dragon_attack) {
											dragon_hp--;
											printf("你打击了巨龙，巨龙生命值：%d\n", dragon_hp);
											pass();
										} else if (player_attack < dragon_attack) {
											player_hp--;
											printf("巨龙打击了你，你的生命值：%d\n", player_hp);
											pass();
										} else {
											printf("双方攻击相抵，不分胜负！\n");
											pass();
										}
									}									
									if (dragon_hp <= 0) {
										printf("你打败了巨龙！\n");	
										pass();
										printf("恭喜你完成了冒险！\n");
										remove("game_save.dat");
									} else {
										printf("你被巨龙打败了！游戏结束\n胜败乃兵家常事，请少侠重新来过\n");	
										pass();
										remove("game_save.dat");
									}									
									return 0;
}

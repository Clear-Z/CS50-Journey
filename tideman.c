#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool check_cycle(int start, int end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) //candidate[i] == argv[i+1]
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) //rank=j ranks[i]=i n=j  更喜欢候选人i而不是j
{
    for (int i = 0; i < candidate_count; i++)//这里是要用<=对吧？candidate_count=argc-1也是从0计数
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) //ranks是一个完整vote的排名 preferences是ij两两比较
{
    for (int i = 0; i < candidate_count; i++)//[i]是排序、ranks[i]=候选人
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)//这样写对吗？我想了40分钟还去看了规格说明和你的预告，我一开始思路总是被candidate[i]干扰，但后来我感觉排名的比较应该是排序自身的比较，也就是第一的永远在与后面所有的比拼中加1票，而第二名在1、2名以外的比拼中全部+一票，以此类推，所以应该是ranks[th]和ranks[th]之间th的比较，而ranks[th]存入的值正好是candidate[]的编号
            {              
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)//这里其实我没懂pair自定义的数组要怎么排列，但我想应该就是ij遍历吧，反正我先写再说。
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)//我感觉我没明白要怎么写出不重复的遍历，不过这样也不能算错？即使重复只是多填了一遍，但pair_count++的问题没有解决，其实我可以return前加一行pair_count=pair_count/2
    {
        for (int j = 0; j <= candidate_count; j++)//可以写成j+1,这样可以省去i>j的判断
        {
            if (i > j)
            {
                if(preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if(preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;//一共有pair_count+1对
                }
            }           
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)//我不明白比较出来的值放在哪，大概是不需要具体几比几的数据所以在设计中省略了，但是这就让我很难跟main函数的思路对齐，导致思路层面的表格为什么要这样设计，对应了那些评选规则我都理解了，但具体要怎么用代码实现我就很乱，总感觉缺数组放数据。
{
    for (int i = 0; i < pair_count; i++)
    {
        int most = i;
        int win = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        for (int n = i + 1; n <= pair_count; n++)
        {
            int win2 = preferences[pairs[n].winner][pairs[n].loser] - preferences[pairs[n].loser][pairs[n].winner];
            if (win < win2)
            {
                most = n; 
                win = win2;              
            }
        }
        if (most != i)
        {
            pair exchange;//这里写arrays[0]意思是该数组只有0这一个空间吗？
            exchange = pairs[i];
            pairs[i] = pairs[most];
            pairs[most] = exchange;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int n = 0; n < pair_count; n++)//失败的人在ij上写下ture
    {
        int winner = pairs[n].winner;
        int loser = pairs[n].loser;
        if (!check_cycle(loser, winner))
        {
            locked[winner][loser] = true; 
        }  
    }
    return;
}

bool check_cycle(int start, int end)
{
    if (start == end)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start][i] == true)
        {
            if (check_cycle(i, end))
            {
                return true;
            }
        }
    }
    return false;    
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if(locked[i][j] == true)
            {
                break; //break打破的是最近的一个for循环吧？还是所有嵌套的循环？
            }
            else if(i == candidate_count - 1)
            {
                printf("%s\n", candidates[j]);
            }
        }
    }
    return;
}
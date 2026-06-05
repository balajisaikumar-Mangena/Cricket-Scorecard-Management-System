//=====================================================================
//                         STRUCTURE DEFINITIONS
//=====================================================================

struct Batsman
{
    char name[6];
    unsigned int runs;
    unsigned int balls;
    unsigned int s_rate;
    unsigned int status;
};

struct Bowler
{
    char name[6];
    unsigned int runs;
    unsigned int wickets;
    unsigned int overs;
    unsigned int balls;
};


//=====================================================================
//                         MATCH VARIABLES
//=====================================================================

extern unsigned int runs;
extern unsigned int wickets;
extern unsigned int overs;
extern unsigned int balls;

extern unsigned int striker;
extern unsigned int non_striker;
extern unsigned int next_batsman;

extern unsigned int current_bowler;
extern unsigned int bowler_change_req;

extern unsigned int toss;
extern unsigned int win;

extern unsigned int target;
extern unsigned int bat;

extern unsigned int innings;

extern float CRR;
extern unsigned int b;
extern unsigned int PS;

extern unsigned char key;


//=====================================================================
//                           TEAM DATABASE
//=====================================================================

extern struct Batsman RCB[11];
extern struct Batsman CSK[11];

extern struct Bowler RCB_bowl[5];
extern struct Bowler CSK_bowl[5];


//=====================================================================
//                         TEAM POINTERS
//=====================================================================

extern struct Batsman *BattingTeam;


//=====================================================================
//                       MATCH CONTROL FUNCTIONS
//=====================================================================

void init_Match(void);
void IPL_intro_UI(void);
void TOSS(void);
void Score(void);
void Winner(void);


//=====================================================================
//                        SCORING FUNCTIONS
//=====================================================================

void Runs(void);
void NoBall(void);
void Freehit(void);
void WideBall(void);
void Wickets(void);
void Balls_Increment(void);
void Innings_Decide(void);


//=====================================================================
//                      DISPLAY FUNCTIONS
//=====================================================================

void TeamScore(void);
void Display_Bowler(void);
void Display_Batsmans(void);
void Current_RR(void);
void Projected_Score(void);


//=====================================================================
//                       UTILITY FUNCTIONS
//=====================================================================

void change_strike(void);
void change_bowler(void);

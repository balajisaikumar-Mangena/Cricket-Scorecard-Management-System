#include <lpc21xx.h>
#include "Score.h"
#include "LCD.h"
#include "KPM.h"
#include "delay.h"

//=====================================================================
//                        TEAM PLAYER DATABASE
//=====================================================================

// RCB Batting Lineup
// Format: {"NAME", Runs, Balls, Fours, Status}
// Status: 1 = Currently Available/Openers, 2 = Yet to Bat
struct Batsman RCB[11] =
{
	{"VIRAT" , 0, 0, 0, 1},   // Opening batsman
	{"SALT"  , 0, 0, 0, 1},   // Opening batsman
	{"DEV P" , 0, 0, 0, 2},   // Middle-order batsman
	{"RAJAT" , 0, 0, 0, 2},   // Middle-order batsman
	{"TIM D" , 0, 0, 0, 2},   // Finisher
	{"JITESH", 0, 0, 0, 2},   // Wicketkeeper batsman
	{"KRUNAL", 0, 0, 0, 2},   // All-rounder
	{"BHUVI" , 0, 0, 0, 2},   // Bowler
	{"JOSH H", 0, 0, 0, 2},   // Bowler
	{"RASIK" , 0, 0, 0, 2},   // Bowler
	{"SUYASH", 0, 0, 0, 2}    // Bowler
};

// RCB Bowling Attack
// Format: {"NAME", Overs, Runs Conceded, Wickets, Economy}
struct Bowler RCB_bowl[5] =
{
	{"KRUNAL", 0, 0, 0, 0},   // Spinner
	{"BHUVI" , 0, 0, 0, 0},   // Fast bowler
	{"JOSH H", 0, 0, 0, 0},   // Fast bowler
	{"RASIK" , 0, 0, 0, 0},   // Medium pacer
	{"SUYASH", 0, 0, 0, 0}    // Spinner
};

// CSK Batting Lineup
struct Batsman CSK[11] =
{
	{"RUTHU" , 0, 0, 0, 1},   // Opening batsman
	{"SANJU" , 0, 0, 0, 1},   // Opening batsman
	{"AYUSH" , 0, 0, 0, 2},   // Middle-order batsman
	{"SHORT" , 0, 0, 0, 2},   // Middle-order batsman
	{"S KHAN", 0, 0, 0, 2},   // All-rounder
	{"KARTIK", 0, 0, 0, 2},   // Middle-order batsman
	{"DUBE"  , 0, 0, 0, 2},   // Power hitter
	{"JAMIE" , 0, 0, 0, 2},   // Bowler
	{"NOOR"  , 0, 0, 0, 2},   // Spinner
	{"HENRY" , 0, 0, 0, 2},   // Fast bowler
	{"KAMBOJ", 0, 0, 0, 2}    // Fast bowler
};

// CSK Bowling Attack
struct Bowler CSK_bowl[5] =
{
	{"DUBE"  , 0, 0, 0, 0},   // Medium pacer
	{"JAMIE" , 0, 0, 0, 0},   // Fast bowler
	{"NOOR"  , 0, 0, 0, 0},   // Spinner
	{"HENRY" , 0, 0, 0, 0},   // Fast bowler
	{"KAMBOJ", 0, 0, 0, 0}    // Fast bowler
};


//=====================================================================
//                     MATCH SCORE VARIABLES
//=====================================================================

unsigned int runs = 0;          // Total team runs
unsigned int wickets = 0;       // Total wickets fallen
unsigned int overs = 0;         // Completed overs
unsigned int balls = 0;         // Current ball count (0-5)


//=====================================================================
//                   CURRENT BATTING PLAYER INDEXES
//=====================================================================

unsigned int striker = 0;       // Current striker batsman index
unsigned int non_striker = 1;   // Current non-striker batsman index
unsigned int next_batsman = 2;  // Next batsman to enter


//=====================================================================
//                   CURRENT BOWLER MANAGEMENT
//=====================================================================

unsigned int current_bowler = 0;     // Active bowler index
unsigned int bowler_change_req = 1;  // Flag for bowler change


//=====================================================================
//                      TOSS & MATCH DECISIONS
//=====================================================================

unsigned int toss;   // Toss winner selection
unsigned int win;    // Match winner


//=====================================================================
//                       INNINGS PARAMETERS
//=====================================================================

unsigned int target; // Target score for 2nd innings
unsigned int bat;    // Batting/Bowling choice after toss


//=====================================================================
//                        MATCH STATISTICS
//=====================================================================

float CRR;           // Current Run Rate
unsigned int b;      // Total balls bowled
unsigned int PS;     // Projected Score


//=====================================================================
//                       INNINGS TRACKER
//=====================================================================

unsigned int innings = 1;   // 1 = First Innings, 2 = Second Innings


//=====================================================================
//                  ACTIVE TEAM POINTERS
//=====================================================================

struct Batsman *BattingTeam; // Points to current batting team
struct Bowler *BowlingTeam;  // Points to current bowling team


//=====================================================================
//                     KEYPAD INPUT VARIABLE
//=====================================================================

unsigned char key;          // Stores keypad key press

//=====================================================================
//                        FUNCTION DEFINITIONS
//=====================================================================


//=====================================================================
//                        MATCH INITIALIZATION
//=====================================================================

void init_Match()
{
	cmd_LCD(0x01);                           // Clear LCD display

	str_LCD(" SMART CRICKET SCOREBOARD ");   // Display project title

	cmd_LCD(0xC0);                           // Move cursor to second line
	str_LCD(" INITIALISING.....  ");         // Initialization message

	delay_s(1);                              // Startup delay
}


//=====================================================================
//                         MATCH INTRO SCREEN
//=====================================================================

void IPL_intro_UI(void)
{
    cmd_LCD(0x01);      // Clear LCD

    cmd_LCD(0x80);      // First line
    str_LCD("      ROYAL CHALLENGERS BANGALORE ");

    cmd_LCD(0xC0);      // Second line
    str_LCD("        VS CHENNAI SUPER KINGS    ");

    delay_ms(1500);     // Team display delay


    cmd_LCD(0x01);      // Clear LCD

    cmd_LCD(0x80);      // First line
    str_LCD("        M CHINNASWAMY STADIUM     ");

    cmd_LCD(0xC0);      // Second line
    str_LCD("              BENGALURU           ");

    delay_ms(1000);     // Venue display delay
}


//=====================================================================
//                           TOSS MANAGEMENT
//=====================================================================

void TOSS(void)
{
    cmd_LCD(0x01);    // Clear LCD

    cmd_LCD(0x80);
    str_LCD("        ====== TOSS TIME ======");

    cmd_LCD(0xC0);
    str_LCD("          HEADS(1)   TAILS(2)");

    // Wait for toss selection
    while(1)
    {
        key = Keypad_Scan();

        if(key=='1' || key=='2')
            break;
    }


    cmd_LCD(0x01);    // Clear LCD

    if(key=='1')
    {
        toss = 1;     // RCB wins toss

        cmd_LCD(0x80);
        str_LCD("          RCB WON THE TOSS");
    }
    else
    {
        toss = 0;     // CSK wins toss

        cmd_LCD(0x80);
        str_LCD("          CSK WON THE TOSS");
    }

    cmd_LCD(0xC0);
    str_LCD("          BAT(1)   BOWL(2)");

    // Wait for batting/bowling choice
    while(1)
    {
        key = Keypad_Scan();

        if(key=='1' || key=='2')
            break;
    }


    cmd_LCD(0x01);    // Clear LCD

    if(toss==1)
    {
        if(key=='1')
        {
            bat = 1;   // RCB chooses batting

            cmd_LCD(0x80);
            str_LCD("          RCB ELECTED TO BAT");

            cmd_LCD(0xC0);
            str_LCD("          MATCH STARTING...");
        }
        else
        {
            bat = 0;   // RCB chooses bowling

            cmd_LCD(0x80);
            str_LCD("          RCB ELECTED TO BOWL");

            cmd_LCD(0xC0);
            str_LCD("          CSK STARTS BATTING");
        }
    }
    else
    {
        if(key=='1')
        {
            bat = 0;   // CSK chooses batting

            cmd_LCD(0x80);
            str_LCD("          CSK ELECTED TO BAT");

            cmd_LCD(0xC0);
            str_LCD("          RCB STARTS BOWLING");
        }
        else
        {
            bat = 1;   // CSK chooses bowling

            cmd_LCD(0x80);
            str_LCD("          CSK ELECTED TO BOWL");

            cmd_LCD(0xC0);
            str_LCD("          RCB STARTS BATTING");
        }
    }

    delay_s(1);      // Display delay

    cmd_LCD(0x01);

    cmd_LCD(0x80);
    str_LCD("        ===== MATCH READY =====");

    cmd_LCD(0xC0);
    str_LCD("            PRESS ANY KEY...");

    key = '\0';

    // Wait for user input
    while(1)
    {
        key = Keypad_Scan();

        if(key)
            break;
    }

    key = '\0';

    cmd_LCD(0x01);   // Clear LCD


    // Assign batting and bowling teams
    if((toss==1 && bat==1) || (toss==0 && bat==0))
    {
        BattingTeam = RCB;
        BowlingTeam = CSK_bowl;
    }
    else
    {
        BattingTeam = CSK;
        BowlingTeam = RCB_bowl;
    }
}

//=====================================================================
//                         STRIKE CHANGE
//=====================================================================

void change_strike(void)
{
    int temp;

    cmd_LCD(0xC0);                 // Move cursor to second line
    str_LCD("             ");      // Clear previous strike information

    temp = striker;                // Store current striker
    striker = non_striker;         // Swap striker
    non_striker = temp;            // Update non-striker
}


//=====================================================================
//                         BOWLER CHANGE
//=====================================================================

void change_bowler(void)
{
    if(!bowler_change_req)         // Exit if bowler change not required
        return;

    key = Keypad_Scan();           // Read keypad input

    if(key == '+')
    {
        current_bowler++;          // Select next bowler

        if(current_bowler >= 5)    // Circular bowler selection
            current_bowler = 0;

        cmd_LCD(0xC0 + 25);        // Bowler display position
        str_LCD("               "); // Clear previous bowler name

        Display_Bowler();          // Display selected bowler
    }

    if(key == '=')
    {
        bowler_change_req = 0;     // Confirm bowler selection

        cmd_LCD(0x01);             // Clear LCD
    }
}


//=====================================================================
//                        RUNS UPDATE
//=====================================================================

void Runs(void)
{
    // Team score update
    runs += (key - '0');

    // Striker statistics update
    BattingTeam[striker].runs += (key - '0');
    BattingTeam[striker].balls++;

    // Current bowler statistics update
    BowlingTeam[current_bowler].runs += (key - '0');

    // Ball and over count update
    if(BowlingTeam[current_bowler].balls == 5)
    {
        BowlingTeam[current_bowler].overs++;  // Complete over

        BowlingTeam[current_bowler].balls = 0;
    }
    else
    {
        BowlingTeam[current_bowler].balls++;  // Increment ball count
    }
}

//=====================================================================
//                           NO BALL
//=====================================================================

void NoBall(void)
{
    key = '\0';

    while(1)
    {
        key = Keypad_Scan();       // Read run scored on no ball

        if((key >= '0' && key <= '4') || key == '6')
        {
            if(key == '1' || key == '3')
                change_strike();   // Change strike for odd runs

            // Team score update
            runs += (key - '0') + 1;

            // Striker statistics update
            BattingTeam[striker].runs += (key - '0');
            BattingTeam[striker].balls++;

            // Bowler statistics update
            BowlingTeam[current_bowler].runs += (key - '0') + 1;

            break;
        }

        if(key == '*')
        {
            key = '0';

            runs += 1;             // No-ball extra only

            BattingTeam[striker].balls++;
            BowlingTeam[current_bowler].runs += 1;

            break;
        }

        if(key == '-')
        {
            key = '0';

            runs += 1;             // No-ball extra only
            BowlingTeam[current_bowler].runs += 1;

            break;
        }
    }

    key = '\0';

    TeamScore();                   // Refresh scoreboard
}


//=====================================================================
//                           FREE HIT
//=====================================================================

void Freehit(void)
{
    key = '\0';

    while(1)
    {
        key = Keypad_Scan();       // Read free-hit result

        if((key >= '0' && key <= '4') || key == '6')
        {
            // Team score update
            runs += (key - '0');

            // Striker statistics update
            BattingTeam[striker].runs += (key - '0');
            BattingTeam[striker].balls++;

            // Bowler statistics update
            BowlingTeam[current_bowler].balls++;
            BowlingTeam[current_bowler].runs += (key - '0');

            Balls_Increment();     // Update match ball count

            if(key == '1' || key == '3')
                change_strike();   // Change strike for odd runs

            break;
        }

        if(key == '*')
        {
            key = '0';

            BattingTeam[striker].balls++;

            BowlingTeam[current_bowler].balls++;

            Balls_Increment();

            break;
        }

        if(key == '-')
        {
            key = '1';

            runs += (key - '0');   // Bye/leg-bye run

            BowlingTeam[current_bowler].runs += (key - '0');
        }

        if(key == '/')
        {
            NoBall();              // Consecutive no-ball
            Freehit();             // Another free hit
        }
    }

    key = '\0';
}


//=====================================================================
//                           WIDE BALL
//=====================================================================

void WideBall(void)
{
    key = '\0';

    while(1)
    {
        key = Keypad_Scan();       // Read additional runs on wide

        if((key >= '0' && key <= '4'))
        {
            if(key == '1' || key == '3')
                change_strike();   // Change strike for odd runs

            break;
        }
    }

    // Team score update
    runs = (runs + 1) + (key - '0');

    // Bowler statistics update
    BowlingTeam[current_bowler].runs += ((key - '0') + 1);

    key = '\0';
}


//=====================================================================
//                        SCOREBOARD UPDATE
//=====================================================================

void TeamScore(void)
{
    // Display batting team name
    cmd_LCD(0x80);

    if(innings == 1)
    {
        (bat) ? str_LCD("RCB ") : str_LCD("CSK ");
    }

    if(innings == 2)
    {
        (!bat) ? str_LCD("RCB ") : str_LCD("CSK ");
    }

    // Display score (Runs/Wickets)
    cmd_LCD(0x80 + 4);

    num_LCD(runs);
    char_LCD('/');
    num_LCD(wickets);

    // Display overs
    cmd_LCD(0x80 + 11);

    num_LCD(overs);
    char_LCD('.');
    num_LCD(balls);

    // Display current batsmen
    Display_Batsmans();

    char_LCD(' ');

    // Display current bowler
    Display_Bowler();

    // Display current run rate
    Current_RR();

    // Display projected score in first innings
    if(innings == 1)
        Projected_Score();
}

//=====================================================================
//                           WICKET HANDLING
//=====================================================================

void Wickets(void)
{
    if(wickets < 10)
    {
        // Dismissed batsman statistics update
        BattingTeam[striker].balls++;
        BattingTeam[striker].status = 0;

        // Bowler statistics update
        BowlingTeam[current_bowler].wickets++;
        BowlingTeam[current_bowler].balls++;

        Balls_Increment();         // Update over and ball count

        wickets++;                 // Increment team wickets

        // Send next batsman to crease
        if(next_batsman < 11)
        {
            striker = next_batsman;
            next_batsman++;

            cmd_LCD(0xC0);
            str_LCD("              "); // Clear batsman display area
        }
    }
    else
    {
        wickets = 10;              // All-out condition
    }
}


//=====================================================================
//                         INNINGS TRANSITION
//=====================================================================

void Innings_Decide(void)
{
    innings = 2;                   // Start second innings

    cmd_LCD(0x01);                 // Clear LCD

    // Set target score
    target = runs + 1;

    // Reset match parameters
    runs = 0;
    balls = 0;
    b = 0;
    overs = 0;
    wickets = 0;
    PS = 0;
    CRR = 0;

    // Reset batting indexes
    next_batsman = 2;
    striker = 0;
    non_striker = 1;

    // Display target score
    cmd_LCD(0x80 + 30);
    str_LCD("TGT : ");
    num_LCD(target);

    // Swap batting and bowling teams
    if(BattingTeam == RCB)
    {
        BattingTeam = CSK;
        BowlingTeam = RCB_bowl;
    }
    else
    {
        BattingTeam = RCB;
        BowlingTeam = CSK_bowl;
    }
}


//=====================================================================
//                           MATCH RESULT
//=====================================================================

void Winning_Logic(void)
{
    if(runs >= target)
    {
        win = 1;   // Batting team wins
    }

    else if(((runs == (target - 1)) && (overs == 2)) ||
            ((wickets == 10) && (runs == (target - 1))))
    {
        win = 3;   // Match tied
    }

    else if((overs == 2) || (wickets == 10))
    {
        win = 2;   // Bowling team wins
    }
}

//=====================================================================
//                         BALL COUNT UPDATE
//=====================================================================

void Balls_Increment(void)
{
    if(balls == 5)
    {
        overs++;                   // Complete current over

        cmd_LCD(0x01);             // Clear LCD

        bowler_change_req = 1;     // Enable bowler selection

        change_strike();           // Change strike at end of over

        balls = 0;                 // Reset ball count
    }
    else
    {
        balls++;                   // Increment ball count

        bowler_change_req = 0;     // No bowler change required
    }

    b++;                           // Increment total balls bowled
}


//=====================================================================
//                          SCORE PROCESSING
//=====================================================================

void Score(void)
{
    key = Keypad_Scan();           // Read match event

    // Runs scored
    if((key >= '0' && key <= '4') || key == '6')
    {
        Runs();

        if((key >= '0' && key <= '4') || key == '6' || key == '*')
        {
            Balls_Increment();
        }
    }

    // Strike rotation
    if(key == '1' || key == '3')
    {
        change_strike();
    }

    // No-ball handling
    if(key == '/')
    {
        NoBall();

        while(1)
        {
            key = Keypad_Scan();

            if(key == '/')
            {
                runs += 1;

                BowlingTeam[current_bowler].runs += 1;

                BattingTeam[striker].balls++;

                NoBall();
            }

            if(key == '-')
            {
                runs += 1;

                BowlingTeam[current_bowler].runs += 1;

                NoBall();
            }

            Freehit();             // Free hit after no-ball

            break;
        }
    }

    // Wide ball handling
    if(key == '-')
    {
        WideBall();
    }

    // Wicket handling
    if(key == '*')
    {
        Wickets();
    }

    // Refresh scoreboard
    TeamScore();
}


//=====================================================================
//                        CURRENT RUN RATE
//=====================================================================

void Current_RR(void)
{
    if(balls == 0 && overs == 0)
    {
        CRR = 0.0;                 // Match just started
    }
    else
    {
        CRR = (runs * 6.0) / b;    // Calculate current run rate
    }

    if((int)CRR < 0)
    {
        CRR = 0;
    }

    cmd_LCD(0x80 + 19);
    str_LCD("CRR ");

    float_LCD(CRR);                // Display current run rate

    cmd_LCD(0x80 + 28);
    char_LCD(' ');                 // Clear extra character
}

//=====================================================================
//                         PROJECTED SCORE
//=====================================================================

void Projected_Score(void)
{
    if(balls == 0 && overs == 0)
    {
        PS = 0;                    // Match not started
    }
    else
    {
        PS = ((runs * 6.0) / b) * 20; // Projected 20-over score
    }

    if(PS < 100)
    {
        cmd_LCD(0x80 + 38);
        str_LCD(" ");
    }

    if(PS < 10)
    {
        cmd_LCD(0x80 + 37);
        str_LCD("  ");
    }

    cmd_LCD(0x80 + 31);
    str_LCD("PS : ");

    num_LCD(PS);                   // Display projected score
}


//=====================================================================
//                        BATSMAN DISPLAY
//=====================================================================

void Display_Batsmans(void)
{
    // Striker details
    cmd_LCD(0xC0);

    str_LCD(BattingTeam[striker].name);
    char_LCD(' ');
    num_LCD(BattingTeam[striker].runs);
    char_LCD('(');
    num_LCD(BattingTeam[striker].balls);
    char_LCD(')');

    char_LCD(' ');

    // Non-striker details
    str_LCD(BattingTeam[non_striker].name);
    char_LCD(' ');
    num_LCD(BattingTeam[non_striker].runs);
    char_LCD('(');
    num_LCD(BattingTeam[non_striker].balls);
    char_LCD(')');
}


//=====================================================================
//                         BOWLER DISPLAY
//=====================================================================

void Display_Bowler(void)
{
    cmd_LCD(0xC0 + 27);

    str_LCD(BowlingTeam[current_bowler].name);
    char_LCD(' ');

    num_LCD(BowlingTeam[current_bowler].wickets);
    char_LCD('-');
    num_LCD(BowlingTeam[current_bowler].runs);

    char_LCD(' ');

    num_LCD(BowlingTeam[current_bowler].overs);
    char_LCD('.');
    num_LCD(BowlingTeam[current_bowler].balls);
}


//=====================================================================
//                          MATCH RESULT
//=====================================================================

void Winner()
{
    // Check result during second innings
    if(innings == 2)
    {
        Winning_Logic();
    }

    // Start second innings
    if((overs == 20 && innings == 1) ||
       (innings == 1 && wickets == 10))
    {
        Innings_Decide();
    }

    // Batting team victory
    if(win == 1)
    {
        cmd_LCD(0x01);

        (!bat) ? str_LCD("RCB ") : str_LCD("CSK ");

        str_LCD("WON BY ");
        num_LCD(10 - wickets);
        str_LCD(" WICKETS");
    }

    // Bowling team victory
    if(win == 2)
    {
        cmd_LCD(0x01);

        (bat) ? str_LCD("RCB ") : str_LCD("CSK ");

        str_LCD("WON BY ");
        num_LCD((target - runs) - 1);
        str_LCD(" RUNS");
    }

    // Match tied
    if(win == 3)
    {
        cmd_LCD(0x01);

        str_LCD("MATCH WAS TIED");
    }
}

#include <iostream>
#include <string>


/**
 * The struct represents a Multiple-Choice Question (MCQ) which includes
 * - the actual question
 * - 4 options to choose from
 * - the correct answer represented as the index of the correct option
 */
struct MCQ {
    std::string question;
    std::string options[4];
    int correct;
};

/**
 * This algorithm assumes we are given 2 banks of MCQs
 * The easy bank consists of 20 easy MCQs
 * The hard bank consists of 20 hard MCQ
 * Depending on the required level (1 for easy, 2 for medium, 3 for difficult),
 * a quiz of 20 MCQ is generated from the 2 question banks.
 */
MCQ* generate_quiz(int level, MCQ* easy, MCQ* hard) {
    auto quiz = new MCQ[20];
    switch(level) {
        case 1:
        // easy quiz only takes questions from the easy bank
        for(int i=0; i<20; i++) {
            quiz[i] = easy[i];
        }
        return quiz;
        case 2:
        // for mediun level, half the questions are from the easy bank, and the oher half is from the hard bank.
        // Set every even question from the easy bank
        // Set evry odd question from the hard bank
        for(int i=0; i<10; i++) {
            quiz[2*i] = easy[2*i + rand() % 2];
            quiz[2*i + 1] = hard[2*i + rand() % 2];
        }
        return quiz;
        case 3:
        // for difficult level, all questions are from hard bank
        for(int i=0; i<20; i++) {
            quiz[i] = hard[i];
        }
        return quiz;
        default:
        delete[] quiz;
        throw std::invalid_argument("invalid level");
    }
}

/**
 * This repeatedly asks the user for difficulty level until he gives a valid answer
 */
int ask_level() {
    int level = 0;
    while(!( 1<= level && level <= 3)) {
        std::cout << "Choose difficulty level (1 - Easy, 2 - Medium, 3 - Difficult): ";
        std::cin >> level;
    }
    std::cout << "level chosen: " << level << "\n";
    return level;
}

/**
 * This function prints out the current quiz question
 */
void ask_question(const MCQ& quiz) {
    std::cout << quiz.question << "\n";
    for(int j = 0; j < 4; j++) {
        std::cout << j+1 << ". " << quiz.options[j] << "\n";
    }
}

/**
 * This function checks if the user's answer is correct for the current quiz question
 */
bool answer_correctly(const MCQ& quiz) {
    int answer;
    std::cin >> answer;
    if(answer == quiz.correct) {
        std::cout << "Correct answer!" << "\n";
        return true;
    }
    std::cout << "Wrong answer! " << "\n";
    return false;
}

/**
 * Each game consists of 20 questions. At the end of 20 questions, it returns the number of questions answered correctly.
 * 
 * The parameter MCQ* quiz is an array of 20 questions.
 */
int start_game(MCQ* quiz) {
    int score = 0;
    for(int i=0; i<20; i++) {
        ask_question(quiz[i]);
        if(answer_correctly(quiz[i])) {
            score++;
        }
        std::cout << "current score: " << score << "\n";
    }
    return score;
}

int main() {
   	MCQ easy_bank[20]=
	{
		{
			"What is the capital of France?", 
			{"London", "Berlin", "Paris", "Madrid"}, 
			3, 
		},
        {
			"How many legs does a spider have?", 
			{"6", "8", "10", "4"}, 
			2, 
		},
        {	"What color do blue and yellow make?", 
			{"Green", "Purple", "Orange", "Brown"}, 
			1,
		},
        {
			"Which planet is known as the Red Planet?", 
			{"Venus", "Mars", "Jupiter", "Saturn"}, 
			2, 
		},
        {	
			"How many days are there in a standard year?", 
			{"364", "365", "366", "360"}, 
			2, 
		},
        {
			"What is the largest ocean on Earth?",
			{"Atlantic", "Indian", "Arctic", "Pacific"},
			4, 
		},
        {"What do bees collect and use to make honey?",
			{"Nectar", "Pollen", "Sap", "Leaves"},
			1, 

		},
        {"How many sides does a triangle have?",
			{"3", "4", "5", "6"},
			1,
		},
        {
			"What is the boiling point of water at sea level?", 
			{"90 C", "100 C", "120 C", "80 C"}, 
			2, 

		},
        {
			"Which animal is known as the King of the Jungle?", 
			{"Elephant", "Tiger", "Lion", "Giraffe"}, 
			3, 
		},
        {
			"Which instrument has 88 keys?", 
			{"Guitar", "Violin", "Flute", "Piano"}, 
			4, 
		},
        {
			"What is the freezing point of water?", 
			{"0 C", "-5 C", "32 C", "10 C"}, 
			1, 
		},
        {
			"How many continents are there on Earth?", 
			{"5", "6", "7", "8"}, 
			3, 
		},
        {
			"Which fruit is associated with Isaac Newton?", 
			{"Orange", "Banana", "Apple", "Grape"}, 
			3, 
		},
        {
			"What is the main language spoken in Brazil?", 
			{"Spanish", "Portuguese", "French", "English"}, 
			2, 
		},
        {
			"What shape is a stop sign?", 
			{"Hexagon", "Octagon", "Pentagon", "Circle"}, 
			2, 
		},
        {
			"What is 5 multiplied by 6?", 
			{"25", "35", "30", "40"}, 
			3, 
		},
        {	
			"Which sense is associated with the nose?", 
			{"Sight", "Touch", "Taste", "Smell"}, 
			4, 
		},
        {
			"What is the hardest natural mineral?", 
			{"Gold", "Iron", "Diamond", "Quartz"}, 
			3, 
		},
        {
			"What is the chemical symbol for water?", 
			{"H2O", "CO2", "O2", "NaCl"}, 
			1,
		},
	};

    MCQ difficult_bank[20]=
	{
		{
			"What is the second most abundant element in the universe?",
			{"Helium", "Hydrogen", "Carbon", "Oxygen"},
			1,
		},
        {
			"Which Roman emperor made his horse a senator?",
			{"Nero", "Caligula", "Commodus", "Claudius"},
			2,
		},
        {
			"What is the half-life of Carbon-14?",
			{"~1,200 years", "~3,500 years", "~5,730 years", "~10,000 years"},
			3,
		},
        {
			"Which treaty ended World War I?",
			{"Treaty of Paris", "Treaty of Versailles", "Treaty of Ghent", "Treaty of Utrecht"},
			2,
		},
        {
			"What is the SI unit of electric capacitance?",
			{"Henry", "Farad", "Weber", "Tesla"},
			2,
		},
        {
			"Who wrote the epic poem 'Paradise Lost'?",
			{"John Milton", "Geoffrey Chaucer", "William Blake", "Lord Byron"},
			1,
		},
        {
			"Which African country was formerly known as Abyssinia?",
			{"Eritrea", "Ethiopia", "Sudan", "Somalia"},
			2,
		},
        {
			"What is the deepest known location on Earth?",
			{"Puerto Rico Trench", "Java Trench", "Mariana Trench", "Tonga Trench"},
			3,
		},
        {
			"In computing, what does RISC stand for?",
			{"Reduced Instruction Set Computer", "Rapid Instruction System Core", "Random Instruction Set Chip", "Redundant Integrated System Cache"},
			1,
		},
        {
			"Which composer wrote the 'Enigma Variations'?",
			{"Edward Elgar", "Gustav Holst", "Benjamin Britten", "Ralph Vaughan Williams"},
			1,
		},
        {
			"What year was the fall of Constantinople?",
			{"1453", "1492", "1204", "1389"},
			1,
		},
        {
			"Which metal is liquid at standard room temperature besides mercury?",
			{"Gallium", "Francium", "Cesium", "Bromine"},
			1,
		},
        {
			"What is the capital of Kazakhstan?",
			{"Almaty", "Astana", "Tashkent", "Bishkek"},
			2,
		},
        {
			"Who discovered the circulation of blood?",
			{"William Harvey", "Andreas Vesalius", "Galen", "Edward Jenner"},
			1,
		},
        {
			"Which battle took place in 1066?",
			{"Battle of Waterloo", "Battle of Agincourt", "Battle of Hastings", "Battle of Bosworth"},
			3,
		},
        {
			"What particle is exchanged in electromagnetic interactions?",
			{"Gluon", "Photon", "W Boson", "Graviton"},
			2,
		},
        {
			"Which philosophical work begins with 'Man is born free, and everywhere he is in chains'?", 
			{"The Social Contract", "Leviathan", "The Republic", "Candide"},
			1,
		},
        {
			"What is the primary ore of aluminum?", 
			{"Bauxite", "Hematite", "Galena", "Cinnabar"}, 
			1,
		},
        {
			"Who was the architect of St. Paul's Cathedral in London?", 
			{"Inigo Jones", "Christopher Wren", "John Vanbrugh", "Nicholas Hawksmoor"}, 
			2,
		},
        {
			"What is the brightest star in the night sky?", 
			{"Betelgeuse", "Rigel", "Sirius", "Vega"}, 
			3,
		}
    };

    std::string player;
    std::cout << "Enter name: ";
    std::cin >> player;
     
    char yes = 'n';
    do {
        auto level = ask_level();
        auto quiz = generate_quiz(level, easy_bank, difficult_bank);
        int score = start_game(quiz);
        delete[] quiz;

        std::cout << "Congrats " << player << " for scoring " << score << "\n";
        std::cout << "Do you want to exit or continue? (y/n)? ";
        std::cin >> yes;
        
    } while(yes == 'y' || yes == 'Y');
    return 0;
}

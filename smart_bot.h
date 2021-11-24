#include <string>

using namespace std;

class Chatbot {
	string name;
public:
	Chatbot(const string& name)
	: name(name)
	{ }

	// Name of this Chatbot
	string get_name() const {
		return name;
	}

	// Give a string to this chatbot.
	virtual void give_msg(const string& s) = 0;
	
	// Get a string from this chatbot.
	virtual string get_msg() = 0;

	// virtual destructor
	virtual ~Chatbot() { }
}; // class Chatbot


//NOTE: THIS WAS MY ORIGINAL IDEA, THE ONLY RESEARCH DONE FOR THIS IS THE FORMULAS FOR CALCULATING MAINTENANCE CALORIES. THOSE MEDICAL RESEARCHES IS FROM BPK143 TEXT BOOK
//Some techniques I used:
//I tried to add some sentences which feels like an actual doctor is saying. 
//I used a vector of positive and sad replies, from which my program will automatically choose responses when needed. 
//Being a BPK student, I tried to make it as correct as possible from the perspective of formulas and advice the doctor is saying. 
//There are some responses, which will automatically finish the conversation. For that I made changes in the converse function.
//Its speciality is it accepts answers in any format like '190', or '190 pounds', or '190 lbs', as long as the answer is within required interval.

class Smart_bot: public Chatbot{

	string doc_name;
	string messagein = "";
	vector<double> measurements;
	vector<string> random_replies = {"Great", "Awesome", "Hmmmmm that seems good to me", "Okay we are good so far", "I hope you not feel it so long, we are almost done"};
	vector<string> positive_replies = {"Yay!", "Great", "Awesome", "Wonderful", "Sounds good"};
	vector<string> sad_replies = {"Okay, It would have been a great experience. Never mind. Hope to see you later.\n", "I believe you are already doing good from health side in your life. Bye now!\n"};


public: 

	//constructor
	Smart_bot(string n)
	: Chatbot(n)
	{
		doc_name = n;
	};

	//give_msg() method
	void give_msg(const string& s){
		messagein = s;
		for_each(messagein.begin(), messagein.end(), [](char & c){
			c = tolower(c);
		});
	};

	//get_msg() method
	string get_msg(){
		int number;
		string messageout;
		if (messagein == ""){
			messageout = "Hi there! My name is " + doc_name + ". I am a professional nutritionist. I can design a diet plan for you based on some of your information. If you are in, you can say yes, otherwise you can say no, I will leave :(\n"; 
			return messageout;
		}
		int response1 = messagein.find("yes");
		int response2 = messagein.find("no");
		if (response1 != std::string::npos){
			number = rand() % positive_replies.size();
			return random_replies[number] + ". First of all I need your gender, 'male' or 'female'. Just want to note that I am not discriminating toward other genders.\n" + 
												"Its just my formulas work with only these two categories. If you don't feel comfortable, I understand, you can terminate the process by writing a no.\n";
		} else if (response2 != std::string::npos) {
			number = rand() % sad_replies.size();
			return sad_replies[number];
		} else {
		}


		//getting an important value that changes the formula based on male and female
		double decision_value = 5;
		int gender_value_1 = messagein.find("fe");
		int gender_value_2 = messagein.find("male");
		if (gender_value_1 != std::string::npos){
			decision_value = -161;
			number = rand() % positive_replies.size();
			return positive_replies[number] + ". Now tell me your age, in years, obviously :)).\n";
		} else if (gender_value_2 != std::string::npos){
			number = rand() % positive_replies.size();
			return positive_replies[number] + ". Now tell me your age, in years, obviously :)). Scientific formulas works correctly when age is between 15 to 80.\n";
		} else{
		}


		//getting age
		double age = stod(messagein);
		if (age >= 15 && age <= 80){
			measurements.push_back(age);
			number = rand() % positive_replies.size();
			return positive_replies[number] + ". Now I would like to know your weight. Please type in your weight in pounds because thats what my calculations are based on.\n Make sure its more than 100 pounds to get correct answer.\n";
		} else if ((age < 15 && age > 5) || (age > 80 && age <100)){ 
			return "I cannot suggest a diet for you as my formulas cannot work with your body measurements. \nFor correct results, your age should be between 15 to 80, weight more than 100 pounds, and height should be atleast 1 metres.\n";
		} else {
		}	


		//getting weight
		double weight = stod(messagein);
		if (weight > 100){
			measurements.push_back(weight);
			number = rand() % random_replies.size();
			return random_replies[number] + ". Whats your height? Please tell me in metres, for the sake of my convenience and my formulas to work. \n Make sure its atleat 1 metre, otherwise formulas will not work.\n";
		} else if(weight <= 100 && weight > 10){
		 	return "I cannot suggest a diet for you as my formulas cannot work with your body measurements. For correct results, your age should be between 15 to 80, weight more than 100 pounds, and height should be atleast 1 metres.\n";
		} else {
		}
	
		//getting height and giving the final result			
		double height = stod(messagein);
		if (height >= 1){
			measurements.push_back(height);
			number = rand() % positive_replies.size();
			double BMR = (10*(measurements[1]/2.2)) + (6.25*(measurements[2]*100)) - (5*(measurements[0])) + (decision_value);
			int no_exercise_maintain = BMR*1.2;
			int little_exercise_maintain = BMR*1.375;
			int moderate_exercise_maintain = BMR*1.55;
			cout << to_string(BMR);
			return positive_replies[number] + "\n" + 
			"So based on my analysis here is my advice for you:\n" + 
			"1. If you are planning to not to exercise and spend most of the day sitting, then your maintenance calories is " + to_string(no_exercise_maintain) + ".\n" + 
			"2. If you are planning to exercise a little like 1 to 3 days a week, then your maintenance calories is " + to_string(little_exercise_maintain) + ".\n" + 
			"3. If you are planning to exercise moderately like 3 to 5 days a week, then your maintenancce calories is " + to_string(moderate_exercise_maintain) + ".\n"
			"4. Note: When I say 1 day of exercise, I mean atleast 45 minutes of elevated heart rate.\n" +
			"5. If you want to loose weight, start with eating 200 calories less than maintenance and check your weight every day.\n If you stop loosing weight, reduce 100 more calories or add 100 calories worth of cardio exercises.\n" + 
			"6. Please add both strength and resistance training in your exercise routine.\n" + 
			"7. Make sure you eat protein 1g per pound of body weight, if you do strength training, and always reduce calories from carbohydrates.\n" + 
			"8. Good luck with your health goals. I hope you will get success. Chat with me again if you see change in your body.\n" +

			"\nIt was nice talking to you. Need to go for another client. Bye now.\n";

		} else if (height < 1) {
			return "I cannot suggest a diet for you as my formulas cannot work with your body measurements. For correct results, your age should be between 15 to 80, weight more than 100 pounds, and height should be atleast 1 metres.\n";
		}

		int last_response = messagein.find("bye");
		if (last_response != std::string::npos){
			return "bye";
		} else return "bye";
		
	

	};

	//destructor
	~Smart_bot()
	{ };
}; 

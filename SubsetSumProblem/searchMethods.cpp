#include <random>
#include <algorithm>
#include <map>
#include "searchMethods.h"

typedef std::mersenne_twister_engine<uint_fast32_t,
        32,624,397,31,0x9908b0df,11,0xffffffff,7,0x9d2c5680,15,0xefc60000,18,1812433253>
        mt19937;
mt19937 mt1(time(nullptr));

int iterationsChecked=0;



using chromosome_t = vector<int>;

vector<int> SolveTabu(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    int tabSize = 1000;
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = {};
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++) {
        int indexToOne = mt1() % (problem.multiset.size());                           //generating a random subset
        if (binaryZeroes.at(indexToOne) == 0)binaryZeroes.at(indexToOne) = 1;
        else j--;
    }
    problem.checked.push_back(binaryZeroes);
    vector<int> bestNeighbour=binaryZeroes;
    for(int i=0;i<iterations;i++, iterationsChecked++){
        //Generate neighbours
        vector<vector<int>> neighbours=findNeighbour(bestNeighbour);
        bestNeighbour= neighbours.at(0);
        for (vector<int> bour : neighbours) {

            if(find(problem.checked.begin(),problem.checked.end(),bour)==problem.checked.end()){
                vector<int> TranslatedBour= translate(problem.multiset,bour);
                if(problem.checkHowCorrect(TranslatedBour)< problem.checkHowCorrect(translate(problem.multiset,bestNeighbour)))bestNeighbour=bour;
            }
        }
        vector<int> trBN = translate(problem.multiset, bestNeighbour);
        if(problem.checkHowCorrect(trBN)<problem.checkHowCorrect(bestSolution))bestSolution=trBN;
        problem.checked.push_back(bestNeighbour);
        if(problem.checked.size()>tabSize){
            problem.checked.erase(problem.checked.begin());
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,trBN);
        int cost = problem.checkHowCorrect(bestSolution);
        if(cost==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return bestSolution;
        }
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveRandomClimbing(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++) {
        int indexToOne = mt1() % (problem.multiset.size());                           //generating a random subset
        if (binaryZeroes.at(indexToOne) == 0)binaryZeroes.at(indexToOne) = 1;
        else j--;
    }

    for(int i=0;i<iterations;i++,iterationsChecked++){
        vector<vector<int>> neighbours = findNeighbour(binaryZeroes);                       //Generating vector filled with new binary forms
        vector<int> tempResult;
        tempResult = translate(problem.multiset,neighbours.at(0));
        if(problem.checkHowCorrect(tempResult)==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        int randomIndex = mt1()%neighbours.size();
        tempResult= translate(problem.multiset,neighbours.at(randomIndex));
        if(problem.checkHowCorrect(tempResult)==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        if(problem.checkHowCorrect(bestSolution)>problem.checkHowCorrect(tempResult)){
            bestSolution = tempResult;
            binaryZeroes=neighbours.at(randomIndex);
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveBruteForce(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress){
    vector<int> multiset = problem.multiset;
    vector<int> tempResult;
    vector<int> bestSolution = {};
    int bestCost = problem.checkHowCorrect(bestSolution);
    vector<int> binaryZeroes;
    int cost;
    binaryZeroes.reserve(problem.multiset.size());
    for (int i = 0; i < problem.multiset.size()&&iterationsChecked<iterations; ++i) {
        binaryZeroes.clear();
        for(int j=0;j<problem.multiset.size()-i;j++){
            binaryZeroes.push_back(0);
        }
        for(int j=0;j<i;j++){
            binaryZeroes.push_back(1);
        }
        do{
            tempResult = translate(problem.multiset,binaryZeroes);
            cost = problem.checkHowCorrect(tempResult);
            if(cost<bestCost){
                bestSolution=tempResult;
                bestCost=cost;
            }
            if(cost==0){
                break;
            }
            iterationsChecked++;
            if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
        }while(std::next_permutation(binaryZeroes.begin(),binaryZeroes.end())&&iterationsChecked<iterations);
    }

    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveClimbing(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++) {
        int indexToOne = mt1() % (problem.multiset.size());                           //generating a random subset
        if (binaryZeroes.at(indexToOne) == 0)binaryZeroes.at(indexToOne) = 1;
        else j--;
    }

    for(int i=0;i<iterations;i++,iterationsChecked++){
        vector<vector<int>> neighbours = findNeighbour(binaryZeroes);                       //Generating vector filled with new binary forms
        vector<int> tempResult;
        tempResult = translate(problem.multiset,neighbours.at(0));
        if(problem.checkHowCorrect(tempResult)==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }
        for(int j=1;j<neighbours.size();j++){
            tempResult = translate(problem.multiset,neighbours.at(j));
            if(problem.checkHowCorrect(tempResult)==0){
                if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
                if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
                return tempResult;
            }
            if(problem.checkHowCorrect(bestSolution)>problem.checkHowCorrect(tempResult)){
                bestSolution = tempResult;
                binaryZeroes=neighbours.at(j);
            }
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveRandomTry(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    int bestCost = problem.checkHowCorrect(bestSolution);
    for(int i=0;i<iterations;i++,iterationsChecked++){
        binaryZeroes = problem.binaryResult;
        //Generate size
        std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
        int size = int_distr(mt1)+1;
        //Generate numbers;
        for(int j=0;j<size;j++){
            int indexToOne = mt1()%(problem.multiset.size());
            if(binaryZeroes.at(indexToOne)==0)binaryZeroes.at(indexToOne)=1;
            else j--;
        }
        vector<int> tempResult = translate(problem.multiset,binaryZeroes);
        int cost = problem.checkHowCorrect(tempResult);
        if(cost==0){
            if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
            if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
            return tempResult;
        }else if(cost<bestCost){
            bestSolution=tempResult;
            bestCost=cost;
        }
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}
vector<int> SolveAnnealing(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress, int temp, std::function<double(int)> T) {
    vector<int> binaryZeroes = problem.binaryResult;
    vector<int> bestSolution = problem.multiset;
    std::uniform_int_distribution<int> rndNgb(0, binaryZeroes.size()-1);
    std::uniform_real_distribution<float> uk(0.0,1.0);
    //Generate size
    std::uniform_int_distribution<int> int_distr(0, problem.multiset.size()-1);
    int size = int_distr(mt1)+1;
    //Generate numbers;
    for(int j=0;j<size;j++){
        int indexToOne = mt1()%(problem.multiset.size());
        if(binaryZeroes.at(indexToOne)==0)binaryZeroes.at(indexToOne)=1;
        else j--;
    }
    vector<int> tempResult = translate(problem.multiset,binaryZeroes);
    bestSolution = tempResult;
    //Annealing
    for(int k=1;k<iterations+1&&problem.checkHowCorrect(bestSolution)!=0;k++,iterationsChecked++){
        if(showProgress)printZb(iterationsChecked,problem,bestSolution,tempResult);
        vector<vector<int>> neighbours = findNeighbour(binaryZeroes);
        vector<int> randomNeighbour = neighbours.at(rndNgb(mt1));
        vector<int> tranlRandNeighw = translate(problem.multiset,randomNeighbour);
        if(problem.checkHowCorrect(tranlRandNeighw)<problem.checkHowCorrect(tempResult)){
            tempResult=tranlRandNeighw;
            binaryZeroes=randomNeighbour;
            if(problem.checkHowCorrect(tempResult)<problem.checkHowCorrect(bestSolution)){
                bestSolution=tempResult;
            }
        }
        else if(uk(mt1)< exp(-1*((abs(problem.checkHowCorrect(tranlRandNeighw)-problem.checkHowCorrect(tempResult)))/T(k)))){
            tempResult=tranlRandNeighw;
            binaryZeroes=randomNeighbour;
            }
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;
    return bestSolution;
}

vector<int> SolveGenetic(Problem problem, int iterations, bool showHwoManyIterations, bool showHowManyChecked, bool showProgress, float p_crossover, float p_mutation, int populationSize, int amountOfElites){
    using namespace std;
    uniform_real_distribution<float> r_crossover(0.0, 1.0);
    std::sort(problem.multiset.begin(), problem.multiset.end());
    population_t population = populate(populationSize,problem.multiset.size());
    vector<double> population_fit(population.size());
    vector<chromosome_t> elites={};
    transform(population.begin(), population.end(), population_fit.begin(),[&problem](chromosome_t chrom){return fitness(problem,chrom);});
    for(int i=0;i<iterations;i++){
        elites.clear();
        vector<int> parents_indexes(population.size());
        population_t new_population(population.size());
        if(amountOfElites!=0)elites=getElites(problem,population,amountOfElites);
        for(int j=0;j<elites.size();j++){
            new_population.at(j)=elites.at(j);
        }
        // calculate selection
        transform(population_fit.begin(), population_fit.end(),
                  parents_indexes.begin(),
                  [&](auto e) { return selectionTournament(population_fit); });
        // perform crossover operations
        for (int j = amountOfElites; j < parents_indexes.size() - 1; j += 2) {
            vector<chromosome_t> offspring = {population[parents_indexes[j]], population[parents_indexes[j + 1]]};

            if (r_crossover(mt1) < p_crossover) {
                offspring = crossover1p(offspring[0],offspring[1]);
            }
            new_population[j] = offspring[0];
            new_population[j + 1] = offspring[1];
        }

        for (int j = amountOfElites; j < new_population.size(); ++j) {
            new_population.at(j)= mutation(new_population.at(j),p_mutation);
        }
        /*
        for (auto &chromosome : new_population) {
            chromosome = mutation(chromosome, p_mutation);
        }*/
        population = new_population;
        std::transform(population.begin(), population.end(), population_fit.begin(),
                       [&problem](chromosome_t chrom){return fitness(problem,chrom);});
        if(showProgress){
            int bestIndex=0;
            for(int j=0;j<population_fit.size();j++){
                if(population_fit[j]>population_fit[bestIndex]){
                    bestIndex=j;
                }
            }
            cout << i << "\t" << problem.checkHowCorrect(population.at(bestIndex)) << endl;
        }
    }
    if(showHwoManyIterations)cout<<"Iterations: "<<iterationsChecked<<endl;
    if(showHowManyChecked)cout<<"Times Checked: "<<problem.HowManyTimesChecked<<endl;

    int bestIndex=0;
    for(int i=0;i<population_fit.size();i++){
        if(population_fit[i]>population_fit[bestIndex]){
            bestIndex=i;
        }
    }
    return translate(problem.multiset,population.at(bestIndex));
}

vector<chromosome_t> getElites(Problem problem, population_t population, int amountOfElites) {
    vector<chromosome_t> elites;
    population_t tempPopulation=population;
    for(int i=0;i<amountOfElites;i++){
        int bestIndex=0;
        for(int j=0;j<tempPopulation.size();j++){
            if(fitness(problem,tempPopulation.at(j)) > fitness(problem,tempPopulation.at(bestIndex))) {
                bestIndex = j;
            }
        }
        elites.push_back(tempPopulation.at(bestIndex));
        tempPopulation.erase(tempPopulation.begin()+bestIndex);
    }
    return elites;
}

int selectionTournament(vector<double> fitnesses) {
    uniform_int_distribution<int> indexRand(0,fitnesses.size()-1);
    int index1=indexRand(mt1),index2=indexRand(mt1);
    return ((fitnesses.at(index1) > fitnesses.at(index2)) ? index1 : index2);
}


population_t populate(int populationSize,int chromosomeSize){
    population_t population;
    for(int i=0;i<populationSize;i++){
        population.push_back(generateRandomSolution(chromosomeSize));
    }
    return population;
}

chromosome_t generateRandomSolution(int size) {
    chromosome_t result;
    uniform_int_distribution bin(0,1);
    for(int i=0;i<size;i++){
        result.push_back(bin(mt1));
    }
    return result;
}

vector<int> translate(vector<int> multiset, vector<int> binaryZeroes) {
    vector<int> Result;
    for (int j = 0; j < binaryZeroes.size(); ++j) {
        if(binaryZeroes.at(j)==1){
            Result.push_back(multiset.at(j));
        }
    }
    return Result;
}

vector<vector<int>> findNeighbour(const vector<int>& binary) {
    vector<vector<int>> neighbours;

    for(int i=0;i<binary.size();i++){
        vector<int> changedBinary=binary;
        changedBinary.at(i)=1-changedBinary.at(i);
        neighbours.push_back(changedBinary);
    }
    return neighbours;
}

double fitness(Problem p, chromosome_t a){
    vector<int> temp;
    temp = translate(p.multiset,a);
    return 1.0f/(p.checkHowCorrect(temp)+1.0f);
}

vector<int> randomNeighbour(const vector<int>& binary){
    vector<vector<int>> neighbours = findNeighbour(binary);
    std::uniform_int_distribution<int> rndNgb(0, neighbours.size()-1);
    return neighbours.at(rndNgb(mt1));
}

void printZb(int iteration,Problem problem, vector<int> bestSolutionSoFar, vector<int> tempSolution){
    cout << iteration << "\t" << problem.checkHowCorrect(bestSolutionSoFar) << "\t" << problem.checkHowCorrect(tempSolution) << endl;
}

chromosome_t mutation(chromosome_t const& preMutation, float p_mutation){
    chromosome_t mutated = preMutation;
    uniform_real_distribution<float> mutation_r(0.0,p_mutation);

    if(p_mutation>mutation_r(mt1)) {
        uniform_int_distribution<int> index(0,mutated.size()-1);
        mutated[index(mt1)]=1-mutated[index(mt1)];
    }
    return mutated;
}

vector<vector<int>> crossover1p(const chromosome_t& p1, const chromosome_t& p2){
    chromosome_t p1c;
    chromosome_t p2c;
    for(int i=0;i<p1.size()/2;i++){
        p1c.push_back(p1.at(i));
        p2c.push_back(p2.at(i));
    }
    for(int i=p1.size()/2;i<p1.size();i++){
        p1c.push_back(p2.at(i));
        p2c.push_back(p1.at(i));
    }
    return {p1c,p2c};
}

/*
// zaczynamy od tego
#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>
std::random_device rd;
std::mt19937 mt_generator(rd());
using chromosome_t = std::vector<int>;
using population_t = std::vector<chromosome_t>;
using fitness_f = std::function<double(const chromosome_t &)>;
using term_condition_f =
 std::function<bool(const population_t &, const std::vector<double> &)>;
using selection_f = std::function<int(const std::vector<double> &)>;
using crossover_f =
 std::function<std::vector<chromosome_t>(const std::vector<chromosome_t> &)>;
using mutation_f = std::function<chromosome_t(chromosome_t, double)>;
population_t genetic_algorithm(population_t initial_population,
 fitness_f fitness,
 term_condition_f term_condition,
 selection_f selection, double p_crossover,
 crossover_f crossover, double p_mutation,
 mutation_f mutation) {
 using namespace std;
 uniform_real_distribution<double> uniform(0.0, 1.0);
 auto population = initial_population;
 vector<double> population_fit(population.size());
 transform(population.begin(), population.end(), population_fit.begin(),
 fitness);
 while (!term_condition(population, population_fit)) {
 vector<int> parents_indexes(population.size());
 population_t new_population(population.size());
 // calculate fitness
 transform(population_fit.begin(), population_fit.end(),
 parents_indexes.begin(),
 [&](auto e) { return selection(population_fit); });
 // perform crossover operations
 for (int i = 0; i < parents_indexes.size() - 1; i += 2) {
 vector<chromosome_t> offspring = {population[parents_indexes[i]], population[parents_indexes[i + 1]]};
 if (uniform(mt_generator) < p_crossover) {
 offspring = crossover(offspring);
 }
 new_population[i] = offspring[0];
 new_population[i + 1] = offspring[1];
 }
 for (auto &chromosome : new_population) {
 chromosome = mutation(chromosome, p_mutation);
 }
 population = new_population;
 std::transform(population.begin(), population.end(), population_fit.begin(),
 fitness);
 }
 return population;
};
using chromosome_t = std::vector<int>;
using population_t = std::vector<chromosome_t>;
int selection_empty(std::vector<double> fitnesses) { return 0; }
std::vector<chromosome_t> crossover_empty(std::vector<chromosome_t> parents) {
 return parents;
}
chromosome_t mutation_empty(chromosome_t parents, double p_mutation) {
 return parents;
}
************************************************************************
 *
 * MINIMAL SET OF FUNCTIONS DEFINING PROBLEM
 *
 *************************************************************************
 * @brief calculates fitness for every population element
 *
 * @param pop the population
 * @return std::vector<double> fitness function values
double fitness_function(const chromosome_t &chromosome) {
    return std::accumulate(chromosome.begin(), chromosome.end(), 0);
}
std::vector<chromosome_t> generate_initial_population(int n) {
    std::vector<chromosome_t> ret(n);
    std::uniform_int_distribution<int> uniform(0, 1);
    std::transform(ret.begin(), ret.end(), ret.begin(), [&](auto e) {
        chromosome_t c(8);
        for (int i = 0; i < c.size(); i++) c[i] = uniform(mt_generator);
        return c;
    });
    return ret;
}
std::ostream &operator<<(std::ostream &o, const chromosome_t chromosome) {
    for (const int p : chromosome) {
        o << p;
    }
    return o;
}
std::ostream &operator<<(std::ostream &o,
                         std::pair<population_t, fitness_f> pop) {
    for (const auto p : pop.first) {
        o << "{" << p << " " << (pop.second(p)) << "} ";
    }
    return o;
}
int main() {
    using namespace std;
    population_t population = generate_initial_population(10);
    auto result = genetic_algorithm(
            population, fitness_function,
            [](auto a, auto b) {
                static int i = 0;
                i++;
                cout << i << ": " << make_pair(a, fitness_function) << endl;
                return i > 10;
            },
            selection_empty, 1.0, crossover_empty, 0.01, mutation_empty);
    cout << make_pair(result, fitness_function);
    cout << endl;
    return 0;
}
 */
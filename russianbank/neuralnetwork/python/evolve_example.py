import csv
import russianbank as rb
import russianbank.neuralnetwork


def main():
    generation = 0
    evolve = rb.neuralnetwork.evolve.Evolve()
    nets = evolve.getNeuralNetworks()
    points = evolve.getPoints()
    with open('results.csv', 'w') as file:
        print("Writing generation {0}".format(generation))
        csvfile = csv.writer(file)
        for i in range(len(points)):
            print(generation, points[i])
            csvfile.writerow([generation, points[i], nets[i].getWeights()])
    for i in range(2):
        generation += 1
        evolve.playMatches()
        evolve.breed()
        evolve.sort()
        nets = evolve.getNeuralNetworks()
        points = evolve.getPoints()
        with open('results.csv', 'w') as file:
            print("Writing generation {0}".format(generation))
            csvfile = csv.writer(file)
            for i in range(len(points)):
                print(generation, points[i])
                csvfile.writerow([generation, points[i], nets[i].getWeights()])


if __name__ == '__main__':
    main()

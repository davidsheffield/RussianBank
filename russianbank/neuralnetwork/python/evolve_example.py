import csv
import russianbank as rb
import russianbank.neuralnetwork


def main():
    generation = 0
    evolve = rb.neuralnetwork.evolve.Evolve()
    nets = evolve.getNeuralNetworks()
    points = evolve.get_points()
    with open('results.csv', 'w') as file:
        print("Writing generation {0}".format(generation))
        csvfile = csv.writer(file)
        for i in range(len(points)):
            print(generation, points[i])
            csvfile.writerow([generation, points[i], nets[i].get_weights()])
    for i in range(2):
        generation += 1
        evolve.play_matches()
        evolve.breed()
        evolve.sort()
        nets = evolve.get_neural_networks()
        points = evolve.get_points()
        with open('results.csv', 'w') as file:
            print("Writing generation {0}".format(generation))
            csvfile = csv.writer(file)
            for i in range(len(points)):
                print(generation, points[i])
                csvfile.writerow([generation, points[i], nets[i].get_weights()])


if __name__ == '__main__':
    main()

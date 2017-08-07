import sys
sys.path.append('build/lib.macosx-10.7-x86_64-3.6/')
import russianbankfield as rb


def main():
    field = rb.RussianBankField()

    field.cardTest()


if __name__ == '__main__':
    main()

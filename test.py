import sys
sys.path.append('build/lib.macosx-10.7-x86_64-3.6/')
import russianbankfield as rb


def main():
    field = rb.RussianBankField(0)

    field.cardTest()


if __name__ == '__main__':
    main()

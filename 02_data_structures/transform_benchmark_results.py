import pandas
import json

fname = "/tmp/result"


def extractMethodName(name):
    return name.split("_")[2]


def extractType(name):
    return name[name.find("<")+1:name.rfind(">")]


def extractIterations(name):
    return int(name.split("/")[1])


def extractParameter(name):
    splitted = name.split("/")
    if len(splitted) == 3:
        return splitted[2]
    else:
        return "default"

def buildDataFrame():
    with open(fname) as fd:
        data = json.load(fd)["benchmarks"]
    df = pandas.DataFrame(data)[["name", "cpu_time"]]
    df["method"] = df["name"].apply(extractMethodName)
    df["type"] = df["name"].apply(extractType)
    df["iterations"] = df["name"].apply(extractIterations)
    df["parameter"] = df["name"].apply(extractParameter)
    df = df.drop(columns="name")
    return df

def main():
    df = buildDataFrame()
    print(df)


if __name__ == "__main__":
    main()

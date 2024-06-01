import os
import argparse
import nbformat
from nbconvert.preprocessors import ClearOutputPreprocessor
from git import Repo, InvalidGitRepositoryError

def clear_outputs_in_directory(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".ipynb"):
                notebook_path = os.path.join(root, file)
                clear_outputs(notebook_path)

def clear_outputs(notebook_path):
    with open(notebook_path, 'r', encoding='utf-8') as f:
        nb = nbformat.read(f, as_version=4)
    clear_output_preprocessor = ClearOutputPreprocessor()
    cleared_nb, _ = clear_output_preprocessor.preprocess(nb, {})
    with open(notebook_path, 'w', encoding='utf-8') as f:
        nbformat.write(cleared_nb, f)

def is_git_repository(path):
    try:
        _ = Repo(path).git_dir
        return True
    except InvalidGitRepositoryError:
        return False

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Clear Jupyter Notebook outputs in a Git repository.')
    parser.add_argument('path', nargs='?', default=os.getcwd(), type=str, help='Path to the Git repository (default: current directory)')

    args = parser.parse_args()
    repo_path = args.path

    if not os.path.isdir(repo_path):
        print(f"The path {repo_path} does not exist or is not a directory.")
    elif not is_git_repository(repo_path):
        print(f"The path {repo_path} is not a valid Git repository.")
    else:
        clear_outputs_in_directory(repo_path)
        print(f"Cleared outputs in Jupyter Notebooks in the repository at {repo_path}.")

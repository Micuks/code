import os
import subprocess
import nbformat as nbf
import subprocess

root_dir = os.getcwd()


def correct_image_path(md_text, nb_path):
    lines = md_text.split("\n")
    corrected_lines = []
    for line in lines:
        if "![" in line and "](" in line and ")" in line:
            image_path = line.split("](")[1].split(")")[0]
            if not image_path.startswith("http"):
                # a relative path
                corrected_path = os.path.join(nb_path, image_path)
                corrected_line = line.replace(image_path, corrected_path)
                corrected_lines.append(corrected_line)
            else:
                corrected_lines.append(line)
        else:
            corrected_lines.append(line)
    return "\n".join(corrected_lines)


def add_latex_package(tex_file):
    with open(tex_file, "r") as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        if line.strip() == "\documentclass[11pt]{article}":
            lines[i] = (
                line
                + "\n\\usepackage{xeCJK}\n"
                + "\\setCJKmainfont{Source Han Sans CN}\n"
                + "\\setCJKmonofont{Source Han Sans CN}\n"
                + "\\author{吴清柳}\n"
            )
            break
    with open(tex_file, "w") as f:
        f.writelines(lines)


# walk through all directories
for dirpath, dirnames, filenames in os.walk("."):
    # for each .ipbnb file
    for filename in [f for f in filenames if f.endswith("train.ipynb")]:
        ipynb_file = os.path.join(dirpath, filename)
        print(dirpath)
        output_dir = dirpath.split(os.sep)[1]
        pdf_file = f"{output_dir}.pdf"
        print(pdf_file)

        # if corresponding .pdf file does not exist
        if True:
            # if not os.path.isfile(pdf_file):
            print(f"generate {pdf_file}")
            # load the notebook
            with open(ipynb_file) as f:
                nb = nbf.read(f, as_version=4)

            # replace relative image paths
            for cell in nb.cells:
                if cell["cell_type"] == "markdown":
                    cell["source"] = correct_image_path(cell["source"], dirpath)

            # save the modified notebook to a temp file
            with open(f"{output_dir}.ipynb", "w") as f:
                nbf.write(nb, f)

            # use nbconvert to convert to .pdf
            subprocess.call(
                [
                    "jupyter",
                    "nbconvert",
                    "--to",
                    "latex",
                    f"{output_dir}.ipynb",
                    "--output-dir",
                    root_dir,
                    "--output",
                    output_dir,
                ]
            )

            # add LaTex packages to support Chinese
            tex_file = f"{output_dir}.tex"
            add_latex_package(tex_file=tex_file)

            # convert to .pdf
            # os.chdir(root_dir)
            subprocess.call(
                [
                    "latexmk",
                    "-pdf",
                    "-xelatex",
                    tex_file,
                ]
            )

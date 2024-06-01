
#PowerShell script to strip out outputs from Jupyter notebooks
$repoPath = Split-Path -Parent $MyInvocation.MyCommand.Path
$files = Get-ChildItem -Path $repoPath -Recurse -Filter *.ipynb
foreach ($file in $files) {
    & conda run -n labenv nbstripout $file.FullName
}

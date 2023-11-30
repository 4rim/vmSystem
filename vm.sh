#!/usr/bin/env zsh

echo 'This program takes some parameters to a virtual memory setup and outputs important metrics, so that you can test your understanding.'
echo 'First, enter the size of the virtual address space:'
read sizeVAS
echo 'Enter the size of the physical address space:'
read sizePAS
echo 'Enter the size of the PPN:'
read sizePPN
echo 'Enter the size of the PTE:'
read sizePTE
echo 'Enter the size of the VPN:'
read sizeVPN
echo 'Enter the size of the page offset:'
read pgOffset

# calculate page offset
if [[ -z ${pgOffset} ]]; then
	if [[ -n "${sizePAS}" ]] && [[ -n "${sizePPN}" ]]; then
		pgOffset=$((sizePAS-sizePPN))
		echo 'The page offset:' $pgOffset
	fi

	if [[ -n "${sizeVAS}" ]] && [[ -n "${sizeVPN}" ]]; then
		pgOffset=$((sizeVAS-sizeVPN))
		echo 'The page offset:' $pgOffset
	fi
fi

# calculate VPN
if [[ -z ${sizeVPN} ]]; then
	if [[ -n "${sizeVAS}" ]] && [[ -n "${sizeVPN}" ]]; then
		sizeVPN=$((sizeVAS-sizeVPN))
		echo 'The size of the VPN:' $sizeVPN
	fi
fi

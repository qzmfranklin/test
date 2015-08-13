import httplib2
import json
import os
import sys

from apiclient import errors
from apiclient import http

from apiclient import discovery
import oauth2client
from oauth2client import client
from oauth2client import tools

try:
    import argparse
    flags = argparse.ArgumentParser(parents=[tools.argparser]).parse_args()
except ImportError:
    flags = None

SCOPES = 'https://www.googleapis.com/auth/drive.readonly'
CLIENT_SECRET_FILE = 'client_secret.json'
APPLICATION_NAME = 'Drive API Quickstart'


def get_credentials():
    """Gets valid user credentials from storage.

    If nothing has been stored, or if the stored credentials are invalid,
    the OAuth2 flow is completed to obtain the new credentials.

    Returns:
        Credentials, the obtained credential.
    """
    home_dir = os.path.expanduser('~')
    credential_dir = os.path.join(home_dir, '.credentials')
    if not os.path.exists(credential_dir):
        os.makedirs(credential_dir)
    credential_path = os.path.join(credential_dir,
                                   'drive-quickstart.json')

    store = oauth2client.file.Storage(credential_path)
    credentials = store.get()
    if not credentials or credentials.invalid:
        flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
        flow.user_agent = APPLICATION_NAME
        credentials = tools.run_flow(flow, store, flags)
        print('Storing credentials to ' + credential_path)
    return credentials

# ...

def print_file_metadata(service, file_id):
  """Print a file's metadata.

  Args:
    service: Drive API service instance.
    file_id: ID of the file to print metadata for.
  """
  try:
    file = service.files().get(fileId=file_id).execute()

    print('Title: %s' % file['title'])
    print('MIME type: %s' % file['mimeType'])
  except (errors.HttpError, error):
    print('An error occurred: %s' % error)


def print_file_content(service, file_id):
  """Print a file's content.

  Args:
    service: Drive API service instance.
    file_id: ID of the file.

  Returns:
    File's content if successful, None otherwise.
  """
  try:
    print(service.files().get_media(fileId=file_id).execute())
  except (errors.HttpError, error):
    print('An error occurred: %s' % error)


def download_file(service, file_id, local_fd):
  """Download a Drive file's content to the local filesystem.

  Args:
    service: Drive API Service instance.
    file_id: ID of the Drive file that will downloaded.
    local_fd: io.Base or file object, the stream that the Drive file's
        contents will be written to.
  """
  request = service.files().get_media(fileId=file_id)
  media_request = http.MediaIoBaseDownload(local_fd, request)

  while True:
    try:
      download_progress, done = media_request.next_chunk()
    except (errors.HttpError, error):
      print('An error occurred: %s' % error)
      return
    if download_progress:
      print('Download Progress: %d%%' % int(download_progress.progress() * 100))
    if done:
      print('Download Complete')
      return

def main():
    """Shows basic usage of the Google Drive API.

    Creates a Google Drive API service object and outputs the names and IDs
    for up to 10 files.
    """
    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    service = discovery.build('drive', 'v2', http=http)

    results = service.files().list(maxResults=10).execute()
    items = results.get('items', [])
    if not items:
        print('No files found.')
    else:
        print('Files:')
        for item in items:
            print('\t{0}\n\t\t{1}'.format(item['title'], item['id']))

    #urx_id = '17fXISIGCuwYz7203sCJRDxbZoP_REVXlRjtu0zWtDuk'
    urx_id = '1B-9vLTh4vsVkEJ8MmODoNF-1BYw-1U-MzO6VNwBvxxs'

    #print_file_metadata(service, urx_id)
    drive_file = service.files().get(fileId=urx_id).execute()
    #json.dump(drive_file, sys.stdout, sort_keys = True, indent = 4, ensure_ascii = False)
    #print('Title: %s' % file['title'])
    #print('MIME type: %s' % file['mimeType'])

    # Download the content
    download_url = drive_file.get('exportLinks')

    #download_url = 'https://docs.google.com/a/fleksy.com/spreadsheets/d/1B-9vLTh4vsVkEJ8MmODoNF-1BYw-1U-MzO6VNwBvxxs/htmlembed'
    download_url = 'https://drive.google.com/uc?id=1B-9vLTh4vsVkEJ8MmODoNF-1BYw-1U-MzO6VNwBvxxs&export=download'

    #download_url = 'https://docs.google.com/spreadsheets/export?id=' + urx_id + '&exportFormat=tsv&gid=0'
    #media_request = http.MediaIoBaseDownload(local_fd, drive_file)
    print(download_url)
    if download_url:
        resp, content = service._http.request(download_url)
        print('Status = ' + str(resp.status))
        print(content.decode())

if __name__ == '__main__':
    main()

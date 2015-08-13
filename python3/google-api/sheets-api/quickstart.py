import json
import gspread
import oauth2client.client
import oauth2client.file
import oauth2client.tools

if __name__ == '__main__':

client_secret_json = json.load(open('client.json', 'r'))['installed']
flow = oauth2client.client.OAuth2WebServerFlow(
        client_id     = client_secret_json['client_id'],
        client_secret = client_secret_json['client_secret'],
        scope         = 'https://spreadsheets.google.com/feeds https://docs.google.com/feeds',
        redirect_uri  = 'http://example.com/auth_return'
        )
storage = oauth2client.file.Storage('creds.data')
credentials = oauth2client.tools.run(flow, storage)

gc = gspread.authorize(credentials)
gc.login()

sht = gc.open_by_url('https://docs.google.com/spreadsheets/d/17fXISIGCuwYz7203sCJRDxbZoP_REVXlRjtu0zWtDuk/edit#gid=0')

wks = sht.sheet1

print wks.get_all_values()
